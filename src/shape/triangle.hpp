/// @file triangle.

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "../lib/tinyobj/tiny_obj_loader.h"
#include "core/param_set.hpp"
#include "core/shape.hpp"
#include "math/point_2.hpp"
#include "math/vector_3.hpp"
#include <memory>

/// This struct implements an indexd triangle mesh database.
struct TriangleMesh {
  /// # of triangles in the mesh.
  size_t n_triangles;
  // The size of the three lists below should be 3 * nTriangles. Every 3 values
  // we have a triangle.
  std::vector<size_t> vertex_indices; // The list of indices to the vertex list,
                                      // for each individual triangle.
  std::vector<size_t> normal_indices; // The list of indices to the normals
                                      // list, for each individual triangle.
  std::vector<size_t> uvcoord_indices; // The list of indices to the UV coord
                                       // list, for each individual triangle.

  // Here comes the data associated with each vertex.
  // WARNING: The length of the vectors below may differ.
  std::vector<Point3> vertices; //!< The 3D geometric coordinates
  std::vector<Vector3> normals; //!< The 3D normals.
  std::vector<Point2> uvcoords; //!< The 2D texture coordinates.

  // Regular constructor (almost all data is imported via move semantics).
  TriangleMesh() = default;
  /// Copy constructor disabled
  TriangleMesh(const TriangleMesh &) = delete;
  /// Assign operator disabled.
  TriangleMesh &operator=(const TriangleMesh &) = delete;
  /// Move constructor.
  TriangleMesh(TriangleMesh &&other) = delete;
};

/// Represents a single triangle.
class Triangle : public Shape {
private:
  /// Pointer to the vertex index array stored in the triangle mesh database.
  size_t *v;
  // After the proper triangle initialization, we may access vertices with v[0],
  // v[1], and v[2]

  /// Pointer to the normal index array stored in the triangle mesh database.
  size_t *n;
  // After the proper triangle initialization, we may access normals with n[0],
  // n[1], and n[2]

  /// Pointer to the UV coord index array stored in the triangle mesh database.
  size_t *uv;
  // After the proper triangle initialization, we may access UV coords with
  // uv[0], uv[1], and uv[2]

  /// This is the **indexed triangle mesh database** this triangle is linked to.
  std::shared_ptr<TriangleMesh> mesh;
  /// Set it `true` to activate backface culling.
  [[maybe_unused]] bool backface_cull;

  Point3 A() const { return mesh->vertices[v[0]]; };
  Point3 B() const { return mesh->vertices[v[1]]; };
  Point3 C() const { return mesh->vertices[v[2]]; };
  Vector3 normA() const { return mesh->normals[n[0]]; };
  Vector3 normB() const { return mesh->normals[n[1]]; };
  Vector3 normC() const { return mesh->normals[n[2]]; };
  Point2 uvA() const { return mesh->uvcoords[uv[0]]; };
  Point2 uvB() const { return mesh->uvcoords[uv[1]]; };
  Point2 uvC() const { return mesh->uvcoords[uv[2]]; };

public:
  Point3 get_center() const override;
  // The single constructor, that receives the mesh, this triangle id, and an
  // indication for backface culling.
  Triangle(std::shared_ptr<TriangleMesh> mesh, size_t tri_id, bool bfc = true)
      : mesh{mesh}, backface_cull{bfc} {
    // This is just a shortcut to access this triangle's data stored in the mesh
    // database.
    v = &mesh->vertex_indices[3 * tri_id];
    n = &mesh->normal_indices[3 * tri_id];
    uv = &mesh->uvcoord_indices[3 * tri_id];
  }
  /// Return the triangle's bounding box.
  // Bounds3f object_bound() const;

  bool intersect_p(const Ray &r) const override;
  std::optional<Surfel> intersect(const Ray &r) const override;

  /// The regular intersection methods, as defined in the Shape parent class.
  // bool intersect(const Ray &ray, float *thit, Surfel *isect) const override {
  //   return true; // This is a stub.
  // }

  /// This friend function helps us debug the triangles, if we want to.
  friend std::ostream &operator<<(std::ostream &os, const Triangle &t);
};

/// This is the entry point for the client. This function begins the process of
/// reading a triangle mesh.
std::vector<std::shared_ptr<Shape>>
create_triangle_mesh_shape(bool flip_normals, const ParamSet &ps);

/// This is the function that actually creates the mesh database and the
/// triangles, ans store them in a Shape list.
std::vector<std::shared_ptr<Shape>>
create_triangle_mesh(std::shared_ptr<TriangleMesh>, bool);

/// Calls the tinyobjloader api to read the OBJ data into memory.
bool load_mesh_data(const std::string &filename, bool rvo, bool cn, bool fn,
                    std::shared_ptr<TriangleMesh> md);

/// This function essentially converts the mesh data from the tinyobjloader
/// internal data structure to our mesh data structure.
void extract_obj_data(const tinyobj::attrib_t &attrib,
                      const std::vector<tinyobj::shape_t> &shapes,
                      bool reverse_order, bool cn, bool fn,
                      std::shared_ptr<TriangleMesh> md);

#endif
