# cod4x-server (Anvil fork)

This is Anvil's fork of callofduty4x/CoD4x_Server. It's public and licensed AGPL-3.0, and it builds as 32-bit x86 (`-m32`). The build instructions are in `README.md`.

How we work is in `.claude/rules/engineering.md`, which loads in every session. The C++ rules in `.claude/rules/cpp.md` apply to our own code only.

## Rules for this repo

- **Our code lives in `plugins/anvil/`.**
  - Change upstream files only when the plugin API can't do the job.
  - Keep those changes minimal, and mark each one with an `// ANVIL:` comment.
- **Never reformat, rename or tidy up upstream code.** It keeps upstream's style, so merges stay clean.
  - Google style applies only inside `plugins/anvil/`.
  - When you create that folder, put a `.clang-format` (`BasedOnStyle: Google`) inside it, never at the repo root.
- **This repo is public.** No secrets, keys, anticheat logic or private backend details. The plugin stays generic: a connection to the backend, plus engine functions.
- **Plugin code runs inside the server frame,** so calls to the backend are asynchronous and never block.

## Commands

- Build: see `README.md`.
- Update from upstream: `git fetch upstream`, then `git merge upstream/master`, then build and run the server.

## Reference

| File | When to read it |
|---|---|
| `.claude/rules/cpp.md` | Loads automatically: C++ style and performance rules |
| `.claude/rules/naming.md` | Loads automatically for code files: how to choose names |
| `../anvil/docs/glossary.md` | The agreed name for every domain concept (it lives in Anvil-CJ/anvil). Check it before naming one |
| `README.md` | Upstream's build and server setup instructions |

## Keeping this file small

Only rules that apply to every task in this repo belong here. Details go in separate docs; add a row to the table above instead of a new section.
