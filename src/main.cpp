#include <pybind11/pybind11.h>
#include "structs.h"
#include "file.h"
#include "node.h"
#include "audio.h"
#include "bitmap.h"

//#include "nx.h"

int add(int i, int j) {
	return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(nx, m) {
	m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: nx

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

	m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

	m.def(
		"subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

	//m.def("load_all", &nl::nx::load_all);

	//m.def("map", []() {
	//	//return &nl::nx::map;
	//	return "string";
	//});

	py::enum_<nl::nodetype>(m, "nodetype", py::arithmetic())
		.value("none", nl::nodetype::none)
		.value("integer", nl::nodetype::integer)
		.value("real", nl::nodetype::real)
		.value("string", nl::nodetype::string)
		.value("vector", nl::nodetype::vector)
		.value("bitmap", nl::nodetype::bitmap)
		.value("audio", nl::nodetype::audio);

	py::class_<nl::node>(m, "node")
		.def(py::init<nl::nodedata const *, nl::filedata const *>())
		.def("get", &nl::node::get)
		.def("name", &nl::node::name)
		.def("size", &nl::node::size)
		.def("data_type", &nl::node::data_type)
		.def("root", &nl::node::root)
		.def("to_string", &nl::node::to_string)
		.def("to_int", &nl::node::to_integer)
		.def("to_real", &nl::node::to_real)
		.def("to_bitmap", &nl::node::to_bitmap, py::return_value_policy::reference_internal)
		.def("to_audio", &nl::node::to_audio)
		.def("x", &nl::node::x)
		.def("y", &nl::node::y)
		.def("resolve", &nl::node::resolve);


	py::class_<nl::file>(m, "file")
		.def(py::init<std::string>())
		.def("root", &nl::file::root)
		.def("string_count", &nl::file::string_count)
		.def("bitmap_count", &nl::file::bitmap_count)
		.def("audio_count", &nl::file::audio_count)
		.def("node_count", &nl::file::node_count)
		.def("get_string", &nl::file::get_string);

	
		//.def(py::init<nl::node::data const *, nl::file::data const *>());
	//	.def("get_integer", &nl::node::get_integer)
	//	.def("get_vector", &nl::node::get_vector)
	//	.def("get_bitmap", &nl::node::get_bitmap)
	//	.def("get_audio", &nl::node::get_audio)
	//	//.def("get_bool", &nl::node::get_bool)
	//	.def("name", &nl::node::name)
	//	.def("size", &nl::node::size)
	//	.def("data_type", &nl::node::data_type)
	//	.def("root", &nl::node::root)
	//	.def("resolve", &nl::node::resolve);
		

	py::class_<nl::audio>(m, "audio")
		.def(py::init<void const *, uint32_t>())
		.def("data", &nl::audio::data)
		.def("length", &nl::audio::length)
		.def("id", &nl::audio::id);

	py::class_<nl::bitmap>(m, "bitmap")
		.def(py::init<void const *, uint16_t, uint16_t>(), py::return_value_policy::reference_internal)
		.def("data", &nl::bitmap::data, py::return_value_policy::reference_internal)
		.def("width", &nl::bitmap::width)
		.def("height", &nl::bitmap::height)
		.def("length", &nl::bitmap::length)
		.def("id", &nl::bitmap::id)
		.def("compressed_size", &nl::bitmap::compressed_size);

#ifdef VERSION_INFO
		m.attr("__version__") = VERSION_INFO;
#else
		m.attr("__version__") = "dev";
#endif
}
