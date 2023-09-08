
#include "asset/import/static_mesh_importer.hpp"
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

std::future<asset*>
static_mesh_importer::async_load_asset(std::unique_ptr<import_task> task)
{
    return std::async(std::launch::async, &static_mesh_importer::load_asset, this, std::move(task));
}
asset*
static_mesh_importer::load_asset(std::unique_ptr<import_task> task)
{
    Assimp::Importer importer;

    const aiScene* scene =
        importer.ReadFile(task->file_path.generic_string(),
                          aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                              aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if (nullptr == scene)
    {
        return nullptr;
    }

    static_mesh_asset* result = new_object<static_mesh_asset>(nullptr);

    for (int i = 0; i < scene->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[i];

        auto indices =
            std::async(std::launch::async, [faces = mesh->mFaces, num_faces = mesh->mNumFaces]() {
                std::vector<std::uint32_t> result;

                for (std::size_t idx = 0; idx < num_faces; ++idx)
                {
                    aiFace* cur = (faces + idx);
                    result.emplace_back(cur->mIndices[0]);
                    result.emplace_back(cur->mIndices[1]);
                    result.emplace_back(cur->mIndices[2]);
                }
                return result;
            });

        auto vertices = std::async(std::launch::async,
                                   [vertices = mesh->mVertices, num = mesh->mNumVertices]() {
                                       std::vector<point3d> result;

                                       for (std::size_t idx = 0; idx < num; ++idx)
                                       {
                                           aiVector3D* cur = (vertices + idx);
                                           result.emplace_back(cur->x, cur->y, cur->z);
                                       }
                                       return result;
                                   });

        result->allocate_mesh_description(indices.get(), vertices.get(), {}, {}, {}, {});
    }

    return result;
}

} // namespace asset

} // namespace ivd