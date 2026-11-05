---
paths:
  - "**/*.{cc,cpp,cxx,h,hpp,hxx,inl}"
---

# C++ rules

This file is shared across all four Anvil-CJ repos, and the master copy is in Anvil-CJ/anvil. In cod4x-server, the style rules apply only to our code in `plugins/anvil/`; upstream code keeps upstream's style.

## Style: Google C++ Style Guide

Follow https://google.github.io/styleguide/cppguide.html. The points below are the ones that matter most; where this list is incomplete, the guide wins.

- **Standard:** C++20, the guide's current target.
- **Formatting:** run clang-format on every file you change, using the repo's `.clang-format`.
- **Naming:**
  - types and functions: `PascalCase`
  - variables and parameters: `snake_case`
  - class data members: `snake_case_`
  - constants and enumerators: `kPascalCase`
  - macros: `UPPER_CASE`, and avoid macros where possible
- **Files:** `snake_case` names ending in `.cc` and `.h`, with `#define` header guards in the form `<PROJECT>_<PATH>_<FILE>_H_`.
- **No exceptions and no RTTI** (`dynamic_cast`, `typeid`). Report errors through return values (a status or result type).
- **Globals:** objects with static storage duration must be trivially destructible, so no global `std::string` or `std::vector`. Use `constexpr`, or a function-local static.
- **Constructors:** mark single-argument constructors and conversion operators `explicit`.
- **Namespaces:** put everything in a namespace, and never write `using namespace`.
- **Ownership:** use `std::unique_ptr`. Use `std::shared_ptr` only when ownership is truly shared. No raw `new` or `delete`.
- **`auto`:** only when the type is obvious from context or can't be written out.
- **`const`:** make everything `const` or `constexpr` that can be.

## Compiler and tools

- **Warnings are errors:** `/W4 /WX /permissive-` on MSVC, `-Wall -Wextra -Wpedantic -Werror` on GCC and Clang.
  - Don't disable a warning to get the build passing; fix the code.
  - If a third-party header causes warnings, isolate that header and say you did it.
- **Tests** use GoogleTest. Hot code gets benchmarks with Google Benchmark.
- **Sanitizers:** run tests under AddressSanitizer where possible (`/fsanitize=address` on MSVC, `-fsanitize=address,undefined` on GCC and Clang).
- **clang-tidy:** once a build exists, run it on the files you changed.

## Performance

Hot code is anything that runs per frame, per usercmd, per server frame or per packet. Hot code follows these rules:

- **No heap allocation.** Preallocate, `reserve`, or use fixed-capacity or arena storage.
- **No waiting or I/O:** no locks, no blocking calls, no file or network I/O and no logging. Write log entries to a preallocated ring buffer and flush it from somewhere else.
- **No indirection in tight loops:** no virtual calls or `std::function` there when a direct call works.

Everywhere:

- **Data layout:** prefer contiguous containers (`std::vector`, `std::array`, flat maps) over node-based ones (`std::map`, `std::list`, and `std::unordered_map` in hot loops). Keep hot data together and avoid pointer chasing.
- **Passing data:** pass large objects by `const&`, and use `std::string_view` or `std::span` for read-only views. Move instead of copying.
- **Measure, don't guess.** Profile or benchmark before and after any change made for performance, and report the numbers. A change that makes hot code slower is a bug, even if the code is cleaner.
- **Cold code:** don't micro-optimize it at the cost of clarity.

## Code inside the game process (client, anticheat)

Our code runs inside the game, so a crash in our code crashes the game and a stall drops frames.

- **Frame budget:** codjump players run 125, 250 or 333 FPS, and some up to 1000. At 333 FPS a frame lasts 3 ms. All our per-frame work combined must stay well under 0.1 ms, and you must measure it.
- **`DllMain`:** only start initialization on a new thread there. No `LoadLibrary`, waits or locks, because `DllMain` runs while Windows holds the loader lock.
- **Hooks:** install and remove them cleanly. Unloading must restore the original code. Hook bodies follow the hot-code rules.
- **Reverse-engineered structs:** the game is 32-bit x86. Every reverse-engineered struct gets `static_assert`s on its size and on the offsets of the fields we use.
- **Game addresses and offsets** live in one file, each labeled with the game and CoD4x client version it belongs to.
  - At startup, check the bytes at every hook site before patching.
  - If they don't match, disable that feature and log it. Never patch without checking.
- **Failures inside hooks:** handle every failure at the hook boundary by disabling the feature and logging it. Never let it crash the game.
