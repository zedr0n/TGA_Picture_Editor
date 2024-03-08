// pybind11_wrapper.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "TGAPicture.h"

namespace py = pybind11;

PYBIND11_MODULE(tgalib, m) {
    py::class_<Picture>(m, "Picture")
        .def(py::init<>()) // Default constructor
        .def(py::init<std::string>()) // Constructor with pictureName
        .def(py::init<std::string, Header, std::vector<Pixel>>()) // Full constructor
        .def("Boundries", &Picture::Boundries)
        .def("ImportDataPixels", &Picture::ImportDataPixels)
        .def("ImportDataHeader", &Picture::ImportDataHeader)
        .def("ImportData", &Picture::ImportData)
        .def("ExportData", &Picture::ExportData, py::arg("filename"), py::arg("folder") = "")
        .def("MultiplyBlend", &Picture::multiplyBlend, py::arg("picture"),py::arg("picture2"), py::arg("filename") = "")
        .def("DiagonalFlip", &Picture::diagonalFlip, py::arg("picture"), py::arg("filename") = "")
        .def("HorizontalFlip", &Picture::horizontalFlip, py::arg("picture"), py::arg("filename") = "")
        .def("VerticalFlip", &Picture::verticalFlip, py::arg("picture"), py::arg("filename") = "")
        .def("SubtractBlend", &Picture::subtractBlend, py::arg("picture"),py::arg("picture2"), py::arg("filename") = "")
        .def("ScreenBlend", &Picture::screenBlend, py::arg("picture"),py::arg("picture2"), py::arg("filename") = "")
        .def("OverlayBlend", &Picture::overlayBlend, py::arg("picture"),py::arg("picture2"), py::arg("filename") = "")
        .def("AddChange", &Picture::AddChange)
        .def("MultiplyChange", &Picture::MultiplyChange)
        .def("SplitRed", &Picture::SplitRed)
        .def("SplitBlue", &Picture::SplitBlue)
        .def("SplitGreen", &Picture::SplitGreen)
        .def("Merge", &Picture::Merge)
        .def("ExtraCredit", &Picture::ExtraCredit)
        .def("TestCompare", &Picture::TestCompare);
        
    //.def("add", &Adder::add)
    //.def("getValue", &Adder::getValue);

}