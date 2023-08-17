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
