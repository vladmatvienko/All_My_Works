#include "model/obj_file_reader.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

namespace s21 {

Scene ObjFileReader::ReadScene(const std::string& path) const {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open OBJ file: " + path);
  }

  std::vector<Point3D> vertices;
  std::vector<Edge> edges;
  std::unordered_set<Edge, EdgeHash> unique_edges;
  std::string line;

  while (std::getline(file, line)) {
    if (IsVertexLine(line)) {
      vertices.push_back(ParseVertex(line));
    } else if (IsFaceLine(line)) {
      const std::vector<std::size_t> face = ParseFace(line, vertices.size());
      if (face.size() >= 2) {
        for (std::size_t i = 0; i < face.size(); ++i) {
          Edge edge(face[i], face[(i + 1) % face.size()]);
          if (unique_edges.insert(edge).second) {
            edges.push_back(edge);
          }
        }
      }
    }
  }

  if (vertices.empty()) {
    throw std::runtime_error("OBJ file has no vertices: " + path);
  }

  Figure figure(std::move(vertices), std::move(edges));
  figure.Normalize();
  return Scene(std::move(figure),
               std::filesystem::path(path).filename().string());
}

bool ObjFileReader::IsVertexLine(const std::string& line) {
  return line.size() >= 2 && line[0] == 'v' &&
         std::isspace(static_cast<unsigned char>(line[1])) != 0;
}

bool ObjFileReader::IsFaceLine(const std::string& line) {
  return line.size() >= 2 && line[0] == 'f' &&
         std::isspace(static_cast<unsigned char>(line[1])) != 0;
}

Point3D ObjFileReader::ParseVertex(const std::string& line) {
  std::istringstream stream(line.substr(1));
  Point3D vertex;
  if (!(stream >> vertex.x >> vertex.y >> vertex.z)) {
    throw std::runtime_error("Incorrect vertex line: " + line);
  }
  return vertex;
}

std::vector<std::size_t> ObjFileReader::ParseFace(const std::string& line,
                                                  std::size_t vertices_count) {
  std::istringstream stream(line.substr(1));
  std::vector<std::size_t> result;
  std::string token;
  while (stream >> token) {
    result.push_back(ParseVertexIndex(token, vertices_count));
  }
  return result;
}

std::size_t ObjFileReader::ParseVertexIndex(const std::string& token,
                                            std::size_t vertices_count) {
  const std::size_t slash_pos = token.find('/');
  const std::string index_text = token.substr(0, slash_pos);
  if (index_text.empty()) {
    throw std::runtime_error("Empty face vertex index");
  }

  long long raw_index = 0;
  try {
    raw_index = std::stoll(index_text);
  } catch (const std::exception&) {
    throw std::runtime_error("Incorrect face vertex index: " + token);
  }

  long long zero_based_index =
      raw_index > 0 ? raw_index - 1
                    : static_cast<long long>(vertices_count) + raw_index;
  if (zero_based_index < 0 ||
      zero_based_index >= static_cast<long long>(vertices_count)) {
    throw std::runtime_error("Face vertex index out of range: " + token);
  }
  return static_cast<std::size_t>(zero_based_index);
}

}  // namespace s21
