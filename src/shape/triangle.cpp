/// @file triangle.cpp
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

#include "math/point_2.hpp"
#include "math/vector_3.hpp"
#include "shape/triangle.hpp"

bool Triangle::intersect_p(const Ray &r) const {
  return intersect(r) != std::nullopt;
}

Point3 Triangle::get_center() const { return (A() + B() + C()) / 3; }

constexpr double EPSILON = 1e-8;

std::optional<Surfel> Triangle::intersect(const Ray &r) const {

  Vector3 edge1 = B() - A();
  Vector3 edge2 = C() - A();

  Vector3 pvec = cross(r.direcao, edge2);
  Vector3 tvec = r.origem - A();
  Vector3 qvec = cross(tvec, edge1);

  double det = dot(edge1, pvec);

  if (backface_cull) {
    if (det < EPSILON)
      return std::nullopt;
  } else {
    if (std::abs(det) < EPSILON)
      return std::nullopt;
  }

  double beta = dot(tvec, pvec) / det;
  double gamma = dot(r.direcao, qvec) / det;
  double t = dot(edge2, qvec) / det;

  if (beta < 0.0 || beta > 1.0)
    return std::nullopt;
  if (gamma < 0.0 || beta + gamma > 1.0)
    return std::nullopt;

  if (t > EPSILON) {
    double alpha = 1.0 - beta - gamma;

    Vector3 nA = normA();
    Vector3 nB = normB();
    Vector3 nC = normC();

    Vector3 interp_normal = alpha * nA + beta * nB + gamma * nC;
    interp_normal = unit_vector(interp_normal);

    if (!backface_cull && det < 0.0) {
      interp_normal = -interp_normal;
    }

    Vector3 outg =
        r.direcao - 2.0 * dot(r.direcao, interp_normal) * interp_normal;

    return Surfel(r(t), interp_normal, outg, t);
  }

  return std::nullopt;
}

/// To help debug triangles.
std::ostream &operator<<(std::ostream &os, const Triangle &t) {
  constexpr short X{0};
  constexpr short Y{1};
  constexpr short Z{2};

  os << "    + V0: (" << t.mesh->vertices[t.v[0]][X] << ", "
     << t.mesh->vertices[t.v[0]][Y] << ", " << t.mesh->vertices[t.v[0]][Z]
     << ")\n"
     << "    + V1: (" << t.mesh->vertices[t.v[1]][X] << ", "
     << t.mesh->vertices[t.v[1]][Y] << ", " << t.mesh->vertices[t.v[1]][Z]
     << ")\n"
     << "    + V2: (" << t.mesh->vertices[t.v[2]][X] << ", "
     << t.mesh->vertices[t.v[2]][Y] << ", " << t.mesh->vertices[t.v[2]][Z]
     << ")\n"

     << "    + N0: (" << t.mesh->normals[t.n[0]][X] << ", "
     << t.mesh->normals[t.n[0]][Y] << ", " << t.mesh->normals[t.n[0]][Z]
     << ")\n"
     << "    + N1: (" << t.mesh->normals[t.n[1]][X] << ", "
     << t.mesh->normals[t.n[1]][Y] << ", " << t.mesh->normals[t.n[1]][Z]
     << ")\n"
     << "    + N2: (" << t.mesh->normals[t.n[2]][X] << ", "
     << t.mesh->normals[t.n[2]][Y] << ", " << t.mesh->normals[t.n[2]][Z]
     << ")\n"

     << "    + UV0: (" << t.mesh->uvcoords[t.uv[0]][X] << ", "
     << t.mesh->uvcoords[t.uv[0]][Y] << ")\n"
     << "    + UV1: (" << t.mesh->uvcoords[t.uv[1]][X] << ", "
     << t.mesh->uvcoords[t.uv[1]][Y] << ")\n"
     << "    + UV2: (" << t.mesh->uvcoords[t.uv[2]][X] << ", "
     << t.mesh->uvcoords[t.uv[2]][Y] << ")\n";

  return os;
}

std::vector<std::shared_ptr<Shape>>
create_triangle_mesh_shape(bool flip_normals, const ParamSet &ps) {
  std::cout << "[TriangleMesh] Iniciando criação da malha...\n";

  bool bkfc_on =
      ps.has("backface_cull") ? ps.retrieve<bool>("backface_cull") : true;
  bool reverse_vertex_order = ps.has("reverse_vertex_order")
                                  ? ps.retrieve<bool>("reverse_vertex_order")
                                  : false;
  bool compute_normals =
      ps.has("compute_normals") ? ps.retrieve<bool>("compute_normals") : false;

  std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>();

  std::string filename =
      ps.has("filename") ? ps.retrieve<std::string>("filename") : "";

  if (!filename.empty()) {
    std::cout << ">>> Carregando malha do arquivo OBJ: " << filename << "\n";
    if (load_mesh_data(filename, reverse_vertex_order, compute_normals,
                       flip_normals, mesh)) {
      std::cout << ">>> Mesh data successfuly loaded!\n";
    } else {
      std::cout << ">>> Mesh data loading failed!\n";
    }
  } else {
    std::cout << ">>> Carregando malha diretamente das tags XML...\n";

    if (ps.has("vertices")) {
      mesh->vertices = ps.retrieve<std::vector<Point3>>("vertices");
      std::cout << "[TriangleMesh] Vértices lidos: " << mesh->vertices.size()
                << "\n";
    }
    if (ps.has("normals")) {
      mesh->normals = ps.retrieve<std::vector<Vector3>>("normals");
      std::cout << "[TriangleMesh] Normais lidas: " << mesh->normals.size()
                << "\n";
    }

    if (ps.has("vertex_indices") &&
        !ps.retrieve<std::vector<size_t>>("vertex_indices").empty()) {
      mesh->vertex_indices = ps.retrieve<std::vector<size_t>>("vertex_indices");
      std::cout << "[TriangleMesh] vertex_indices encontrados: "
                << mesh->vertex_indices.size() << "\n";
    } else if (ps.has("indices")) {
      mesh->vertex_indices = ps.retrieve<std::vector<size_t>>("indices");
      std::cout << "[TriangleMesh] indices (fallback) encontrados: "
                << mesh->vertex_indices.size() << "\n";
    }

    if (ps.has("normal_indices")) {
      mesh->normal_indices = ps.retrieve<std::vector<size_t>>("normal_indices");
      std::cout << "[TriangleMesh] normal_indices encontrados: "
                << mesh->normal_indices.size() << "\n";
    }

    mesh->n_triangles =
        mesh->vertex_indices.empty() ? 0 : mesh->vertex_indices.size() / 3;
    std::cout << "[TriangleMesh] Total de triângulos calculados: "
              << mesh->n_triangles << "\n";

    if (!mesh->normals.empty() && mesh->normal_indices.empty()) {
      mesh->normal_indices = mesh->vertex_indices;
      std::cout
          << "[TriangleMesh] Fallback 1:1 aplicado para normal_indices.\n";
    }

    if (mesh->normals.empty()) {
      mesh->normals.emplace_back(0.0f, 1.0f, 0.0f);
      std::cout << "[TriangleMesh] Injetando normal dummy (0, 1, 0)...\n";
    }
    if (mesh->normal_indices.empty()) {
      mesh->normal_indices.resize(mesh->vertex_indices.size(), 0);
      std::cout << "[TriangleMesh] Preenchendo normal_indices com tamanho "
                << mesh->normal_indices.size() << "...\n";
    }

    if (mesh->uvcoords.empty()) {
      mesh->uvcoords.emplace_back(0.0f, 0.0f);
    }
    if (mesh->uvcoord_indices.empty()) {
      mesh->uvcoord_indices.resize(mesh->vertex_indices.size(), 0);
      std::cout << "[TriangleMesh] Preenchendo uvcoord_indices com tamanho "
                << mesh->uvcoord_indices.size() << "...\n";
    }

    if (reverse_vertex_order) {
      std::cout
          << "[TriangleMesh] Aplicando Reverse Vertex Order no winding...\n";
      for (size_t i = 0; i < mesh->vertex_indices.size(); i += 3) {
        std::swap(mesh->vertex_indices[i], mesh->vertex_indices[i + 2]);
        std::swap(mesh->normal_indices[i], mesh->normal_indices[i + 2]);
        std::swap(mesh->uvcoord_indices[i], mesh->uvcoord_indices[i + 2]);
      }
    }
  }

  std::cout << "[TriangleMesh] Malha pronta. Gerando shapes e retornando...\n";
  return create_triangle_mesh(mesh, bkfc_on);
}

/// This function calls the basic tinyobjloader loading function and stores all
/// the data into the tinyobjloader's internal data structures.
bool load_mesh_data(const std::string &filename, bool rvo, bool cn, bool fn,
                    std::shared_ptr<TriangleMesh> md) {
  // Default load parameters
  const char *basepath = nullptr;
  bool triangulate = true;

  std::cout << "Loading " << filename << '\n';

  // This is the tinyobj internal data structures.
  tinyobj::attrib_t
      attrib; // Hold all the data, such as vertex, normals, UV coords
  std::vector<tinyobj::shape_t>
      shapes; // Represents a collection of faces, grouped in a unit.
  std::vector<tinyobj::material_t> materials; // Materials, NOT USED HERE.

  // Warnings and Error values.
  std::string warn;
  std::string err;

  // Timing loading.
  //================================================================================
  // auto start = std::chrono::steady_clock::now();
  //================================================================================
  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                              filename.c_str(), basepath, triangulate);
  //================================================================================
  // std::chrono::time_point<std::chrono::steady_clock> end =
  //     std::chrono::steady_clock::now();
  // // Store the time difference between start and end
  // std::chrono::duration<double> diff = end - start;

  // // Milliseconds (10^-3)
  // std::cout << "\t\t>>> "
  //           << std::chrono::duration<double, std::milli>(diff).count() << "
  //           ms"
  //           << '\n';

  // // Nanoseconds (10^-9)
  // std::cout << "\t\t>>> "
  //           << std::chrono::duration<double, std::nano>(diff).count() << "
  //           ns"
  //           << '\n';

  // // Seconds
  // auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
  // std::cout << "\t\t>>> " << diff_sec.count() << " s" << '\n';
  //================================================================================

  if (!warn.empty()) {
    std::cout << "WARN: " << warn << '\n';
  }

  if (!err.empty()) {
    std::cerr << "ERR: " << err << '\n';
  }

  if (!ret) {
    std::cout << "Failed to load/parse .obj.\n";
    return false;
  }

  // Let us now "convert" or "migrate" the data from tinyobjloader data
  // structure into our mesh data format.
  extract_obj_data(attrib,
                   shapes, // TinyObjeLoader data structures (IN)
                   rvo, cn,
                   fn,  // Mesh modifiers (IN)
                   md); // Reference to the mesh data to fill in. (OUT)

  return true;
}

/**
 * This is the function that converts from the tinyobjloader's internal storage
 * to our mesh data organization.
 */
void extract_obj_data(const tinyobj::attrib_t &attrib,
                      const std::vector<tinyobj::shape_t> &shapes,
                      bool reverse_order, [[maybe_unused]] bool cn, bool fn,
                      /* OUT */ std::shared_ptr<TriangleMesh> md) {
  // std::cout << "-- SUMMARY of the OBJ file --\n";
  // std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << '\n';
  // std::cout << "# of normals   : " << (attrib.normals.size() / 3) << '\n';
  // std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2) << '\n';
  // std::cout << "# of shapes    : " << shapes.size() << '\n';
  // std::cout << "-----------------------------\n";

  // Retrieve the complete list of vertices.
  auto n_vertices{attrib.vertices.size() / 3};
  for (auto idx_v{0U}; idx_v < n_vertices; idx_v++) {
    // std::cout << "   v[" << static_cast<long>(idx_v) << "] = ( "
    //           << static_cast<double>(attrib.vertices[(3 * idx_v) + 0]) << ",
    //           "
    //           << static_cast<double>(attrib.vertices[(3 * idx_v) + 1]) << ",
    //           "
    //           << static_cast<double>(attrib.vertices[(3 * idx_v) + 2])
    //           << " )\n";

    // Store the vertex in the mesh data structure.
    md->vertices.push_back(Point3{attrib.vertices[(3 * idx_v) + 0],
                                  attrib.vertices[(3 * idx_v) + 1],
                                  attrib.vertices[(3 * idx_v) + 2]});
  }

  // Read the normals
  // TODO: flip normals if requested.
  tinyobj::real_t flip = (fn) ? -1 : 1;
  auto n_normals{attrib.normals.size() / 3};

  // Do we need to compute the normals? Yes only if the user requeste or there
  // are no normals in the file. if ( cn == true or n_normals == 0)
  // {
  //    // TODO: COmpute normals here.
  //    // compute_normals();
  // }
  // else {// Read normals from file. This corresponds to the entire 'for'
  // below.

  // Traverse the normals read from the OBJ file.
  for (auto idx_n{0U}; idx_n < n_normals; idx_n++) {
    // std::cout << "   n[" << static_cast<long>(idx_n) << "] = ( "
    //           << static_cast<double>(attrib.normals[(3 * idx_n) + 0]) << ", "
    //           << static_cast<double>(attrib.normals[(3 * idx_n) + 1]) << ", "
    //           << static_cast<double>(attrib.normals[(3 * idx_n) + 2]) << "
    //           )\n";

    // Store the normal.
    md->normals.push_back(Vector3{attrib.normals[(3 * idx_n) + 0] * flip,
                                  attrib.normals[(3 * idx_n) + 1] * flip,
                                  attrib.normals[(3 * idx_n) + 2] * flip});
  }

  // Read the complete list of texture coordinates.
  auto n_texcoords{attrib.texcoords.size() / 2};
  for (auto idx_tc{0U}; idx_tc < n_texcoords; idx_tc++) {
    // std::cout << "   t[" << static_cast<long>(idx_tc) << "] = ( "
    //           << static_cast<double>(attrib.texcoords[(2 * idx_tc) + 0]) <<
    //           ", "
    //           << static_cast<double>(attrib.texcoords[(2 * idx_tc) + 1])
    //           << " )\n";

    // Store the texture coords.
    md->uvcoords.push_back(Point2{attrib.texcoords[(2 * idx_tc) + 0],
                                  attrib.texcoords[(2 * idx_tc) + 1]});
  }

  // Read mesh connectivity and store it as lists of indices to the real data.
  auto n_shapes{shapes.size()};
  md->n_triangles = 0; // We must reset this here.
  // In case the OBJ file has the triangles organized in several shapes or
  // groups, we ignore this and store all triangles as a single mesh dataset.
  // This is why we need to reset the triangle count here.
  for (auto idx_s{0U}; idx_s < n_shapes; idx_s++) {
    // std::cout << "The shape[" << idx_s << "].name = " << shapes[idx_s].name
    //           << '\n';
    // std::cout << "Size of shape[" << idx_s << "].mesh.indices: "
    //           << static_cast<unsigned
    //           long>(shapes[idx_s].mesh.indices.size())
    //           << '\n';
    // std::cout << "shape[" << idx_s << "].num_faces: "
    //           << static_cast<unsigned long>(
    //                  shapes[idx_s].mesh.num_face_vertices.size())
    //           << '\n';

    // For each face print out the indices lists.
    size_t index_offset = 0;
    // # of triangles for this "shape" (group).
    // NOTE that we are accumulate the number of triangles coming from the
    // shapes present in the OBJ file.
    md->n_triangles += shapes[idx_s].mesh.num_face_vertices.size();
    for (size_t idx_f{0}; idx_f < md->n_triangles; idx_f++) {
      // Number of vertices per face (always 3, in our case)
      size_t fnum = shapes[idx_s].mesh.num_face_vertices[idx_f];

      // std::cout << "  face[" << idx_f
      //           << "].fnum = " << static_cast<unsigned long>(fnum) << '\n';

      // TODO: Invert order of vertices if flag is on. (DONE!)
      if (reverse_order) {
        // std::cout << "Reverse order\n";
        // For each vertex in the face print the corresponding indices
        for (size_t v = fnum - 1; v >= 0; v--) {
          tinyobj::index_t idx = shapes[idx_s].mesh.indices[index_offset + v];
          // std::cout << "    face[" << idx_f << "].v[" << v
          //           << "].indices = " << idx.vertex_index << "/"
          //           << idx.normal_index << "/" << idx.texcoord_index << '\n';
          // Add the indices to the global list of indices we need to pass on to
          // the mesh object.
          md->vertex_indices.push_back(static_cast<size_t>(idx.vertex_index));
          md->normal_indices.push_back(static_cast<size_t>(idx.normal_index));
          md->uvcoord_indices.push_back(
              static_cast<size_t>(idx.texcoord_index));
        }
      } else { // Keep the original vertex order
        // For each vertex in the face get the corresponding indices
        for (size_t v = 0; v < fnum; v++) {
          tinyobj::index_t idx = shapes[idx_s].mesh.indices[index_offset + v];
          // std::cout << "    face[" << idx_f << "].v[" << v
          //           << "].indices = " << idx.vertex_index << "/"
          //           << idx.normal_index << "/" << idx.texcoord_index << '\n';
          // Add the indices to the global list of indices we need to pass on to
          // the mesh object. This goes to the mesh data structure.
          md->vertex_indices.push_back(static_cast<size_t>(idx.vertex_index));
          md->normal_indices.push_back(static_cast<size_t>(idx.normal_index));
          md->uvcoord_indices.push_back(
              static_cast<size_t>(idx.texcoord_index));
        }
      }

      // Advance over to the next triangle.
      index_offset += fnum;
    }
  }

  // std::cout << "This is the list of indices: \n";

  // std::cout << "   + Vertices [ ";
  // std::copy(md->vertex_indices.begin(), md->vertex_indices.end(),
  //           std::ostream_iterator<int>(std::cout, " "));
  // std::cout << "]\n";

  // std::cout << "   + Normals [ ";
  // std::copy(md->normal_indices.begin(), md->normal_indices.end(),
  //           std::ostream_iterator<int>(std::cout, " "));
  // std::cout << "]\n";

  // std::cout << "   + UV coords [ ";
  // std::copy(md->uvcoord_indices.begin(), md->uvcoord_indices.end(),
  //           std::ostream_iterator<int>(std::cout, " "));
  // std::cout << "]\n";
}

/// This function creates the internal data structure, required by the RT3.
std::vector<std::shared_ptr<Shape>>
create_triangle_mesh(std::shared_ptr<TriangleMesh> mesh, bool backface_cull) {
  // List of shapes (triangles) we need to return to the client.
  std::vector<std::shared_ptr<Shape>> tris;
  // Create the triangles, which are just references to the mesh database.
  tris.reserve(mesh->n_triangles);
  for (size_t i = 0; i < mesh->n_triangles; ++i) {
    tris.emplace_back(std::make_shared<Triangle>(mesh, i, backface_cull));
  }
  return tris;
}
