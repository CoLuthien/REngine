
#include "static_mesh_importer.hpp"
#include "asset/static_mesh_asset.hpp"

#include "object_allocators.hpp"

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h>      // Output data structure
#include <assimp/postprocess.h>

#include <future>

namespace ivd
{
namespace asset
{
namespace importer
{

std::vector<std::shared_ptr<static_mesh_description>>
load_static_mesh(fs::path const& filename)
{
    Assimp::Importer importer;
    const aiScene*   scene =
        importer.ReadFile(filename.generic_string(),
                          aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                              aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if (nullptr == scene)
    {
        return {};
    }
    std::vector<std::shared_ptr<static_mesh_description>> result;

    auto&& load_point_atrrib = []<class AttributeType>(AttributeType* attrib, std::size_t num) {
        std::vector<point3d> result;
        result.reserve(num);
        for (std::size_t idx = 0; idx < num; ++idx)
        {
            aiVector3D* cur = (attrib + idx);
            result.emplace_back(cur->x, cur->y, cur->z);
        }
        return result;
    };

    auto&& load_vector_atrrib = []<class AttributeType>(AttributeType* attrib,
                                                        std::size_t    num) -> auto {
        std::vector<vector3d> result;
        result.reserve(num);
        if (attrib)
        {
            for (std::size_t idx = 0; idx < num; ++idx)
            {
                aiVector3D* cur = (attrib + idx);
                result.emplace_back(cur->x, cur->y, cur->z);
            }
        }
        return result;
    };

    for (int i = 0; i < scene->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[i];

        auto indices =
            std::async(std::launch::async, [faces = mesh->mFaces, num_faces = mesh->mNumFaces]() {
                std::vector<std::uint32_t> result;
                result.reserve(num_faces);

                for (std::size_t idx = 0; idx < num_faces; ++idx)
                {
                    aiFace* cur = (faces + idx);
                    result.emplace_back(cur->mIndices[0]);
                    result.emplace_back(cur->mIndices[1]);
                    result.emplace_back(cur->mIndices[2]);
                }
                return result;
            });

        auto vertices =
            std::async(std::launch::async, load_point_atrrib, mesh->mVertices, mesh->mNumVertices);
        auto normals =
            std::async(std::launch::async, load_vector_atrrib, mesh->mNormals, mesh->mNumVertices);
        auto tangents =
            std::async(std::launch::async, load_vector_atrrib, mesh->mTangents, mesh->mNumVertices);
        auto bitangents = std::async(
            std::launch::async, load_vector_atrrib, mesh->mBitangents, mesh->mNumVertices);
        auto texcoords = std::async(
            std::launch::async, load_vector_atrrib, mesh->mTextureCoords[0], mesh->mNumVertices);
        result.emplace_back(std::make_shared<static_mesh_description>(
            static_mesh_description{.m_indices    = indices.get(),
                                    .m_vertices   = vertices.get(),
                                    .m_normals    = normals.get(),
                                    .m_texcoords  = texcoords.get(),
                                    .m_tangents   = tangents.get(),
                                    .m_bitangents = bitangents.get()}));
    }

    return result;
}

} // namespace importer

} // namespace asset

} // namespace ivd