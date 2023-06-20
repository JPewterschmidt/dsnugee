add_rules("mode.debug")

add_requires("fmt", "gflags", "gtest")
add_packages("fmt", "gflags", "gtest")
set_languages("c++2b")
set_toolset("cc", "gcc")
set_toolset("cxx", "g++")

target("dsnugee")
    set_version("0.0.1")
    set_kind("shared")
    set_warnings("all", "error")
    add_cxflags("-Wconversion", { force = true })
    add_includedirs("src", { public = true })
    add_files(
        "src/*.cc"
    )
    set_toolchains("gcc")
    set_policy("build.optimization.lto", true)
    on_install(function (target)
        -- nothing
    end)

target("dsnugee-unittest")
    add_packages("gtest")
    set_kind("binary")
    add_files("tests/*.cc")

    set_policy("build.optimization.lto", true)
    add_deps("dsnugee")
    add_packages("gtest")
    set_toolchains("gcc")
    add_includedirs("src", { public = true })
    on_install(function (target)
        -- nothing
    end)
    after_build(function (target)
        print("✔ execute unit tests: ✔ ")
        os.exec(target:targetfile())
    end)
    on_run(function (target)
        -- nothing
    end)

target("example")
    --add_syslinks("asan", { force = true })
    add_cxflags("-Wconversion", { force = true })
    add_files("examples/*.cc", "src/*.cc")
    add_includedirs("src", { public = true })
    set_toolchains("gcc")
    set_values("debug", true)
    set_values("symbols", "debug")
    set_optimize("none")
    --add_cxflags("-fsanitize=address", { force = true })
    --add_cxflags("-fno-inline", { force = true })
    on_install(function (target)
        -- nothing
    end)

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

