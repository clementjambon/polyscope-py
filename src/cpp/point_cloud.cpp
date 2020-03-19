#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/point_cloud.h"
#include "polyscope/polyscope.h"

namespace py = pybind11;
namespace ps = polyscope;


// clang-format off
void bind_point_cloud(py::module& m) {

  // Helper classes
  py::class_<ps::PointCloudColorQuantity>(m, "PointCloudColorQuantity");
  py::class_<ps::PointCloudScalarQuantity>(m, "PointCloudScalarQuantity")
    .def("set_enabled", &ps::PointCloudScalarQuantity::setEnabled, "Set enabled")
    .def("set_color_map", &ps::PointCloudScalarQuantity::setColorMap, "Set color map")
    .def("set_map_range", &ps::PointCloudScalarQuantity::setMapRange, "Set map range");
  py::class_<ps::PointCloudVectorQuantity>(m, "PointCloudVectorQuantity");

  // Main class, with adder methods
  py::class_<ps::PointCloud>(m, "PointCloud")

    // basics
    .def("remove", &ps::PointCloud::remove, "Remove the structure")
    .def("set_enabled", &ps::PointCloud::setEnabled, "Enable the structure")
    .def("is_enabled", &ps::PointCloud::isEnabled, "Check if the structure is enabled")
    .def("remove_all_quantities", &ps::PointCloud::removeAllQuantities, "Remove all quantities")
    .def("remove_quantity", &ps::PointCloud::removeQuantity, "Remove a quantity")
    .def("update_point_positions", &ps::PointCloud::updatePointPositions<Eigen::MatrixXd>, "Update point positions")
    .def("update_point_positions2D", &ps::PointCloud::updatePointPositions2D<Eigen::MatrixXd>, "Update point positions")

    // options
    .def("set_point_radius", &ps::PointCloud::setPointRadius, "Set radius")
    .def("get_point_radius", &ps::PointCloud::getPointRadius, "Get radius")
    .def("set_point_color", &ps::PointCloud::setPointColor, "Set color")
    .def("get_point_color", &ps::PointCloud::getPointColor, "Get color")
    .def("set_material", &ps::PointCloud::setMaterial, "Set material")
    .def("get_material", &ps::PointCloud::getMaterial, "Get material")

    // quantities
    .def("add_color_quantity", &ps::PointCloud::addColorQuantity<Eigen::MatrixXd>, "Add a color function at points",
        py::arg("name"), py::arg("values"), py::return_value_policy::reference)
    .def("add_scalar_quantity", &ps::PointCloud::addScalarQuantity<Eigen::VectorXd>, "Add a scalar function at points",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_vector_quantity", &ps::PointCloud::addVectorQuantity<Eigen::MatrixXd>, "Add a vector function at points",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference);

  // Static adders and getters
  m.def("register_point_cloud", &ps::registerPointCloud<Eigen::MatrixXd>, 
      py::arg("name"), py::arg("values"), py::arg("errorIfPresent")=false,
      "Register a point cloud", py::return_value_policy::reference);
  m.def("register_point_cloud2D", &ps::registerPointCloud2D<Eigen::MatrixXd>, 
      py::arg("name"), py::arg("values"), py::arg("errorIfPresent")=false,
      "Register a point cloud", py::return_value_policy::reference);
  m.def("remove_point_cloud", &polyscope::removePointCloud, "Remove a point cloud by name");
  m.def("get_point_cloud", &polyscope::getPointCloud, "Get a point cloud by name", py::return_value_policy::reference);
  m.def("has_point_cloud", &polyscope::hasPointCloud, "Check for a point cloud by name");

}
// clang-format on