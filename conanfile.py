from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout

class TheMinerzCoinConan(ConanFile):
    name = "TheMinerzCoin"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    options = {"with_gui": [True, False], "with_rust": [True, False]}
    default_options = {"with_gui": True, "with_rust": False}
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "*"

    def requirements(self):
        self.requires("boost/1.85.0")
        self.requires("openssl/3.2.0")
        self.requires("miniupnpc/2.2.6")
        self.requires("blst/0.3.10")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["WITH_GUI"] = "ON" if self.options.with_gui else "OFF"
        tc.variables["WITH_RUST"] = "ON" if self.options.with_rust else "OFF"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

