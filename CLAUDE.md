# cod4x-server (Anvil fork)

This is Anvil's fork of callofduty4x/CoD4x_Server. It's public and licensed AGPL-3.0, and it builds as 32-bit x86 (`-m32`). The build instructions are in `README.md`.

It holds upstream's code plus the few engine patches our plugin needs. The plugin itself is in the private repo Anvil-CJ/anvil-plugin, which pins this repo as a git submodule and builds both.

How we work is in `.claude/rules/engineering.md`, which loads in every session.

## Rules for this repo

- **Change upstream files only when the plugin API can't do the job.**
  - Keep those changes minimal, and mark each one with an `// ANVIL:` comment.
  - An engine patch lands here first. Then anvil-plugin moves its submodule to the new commit, together with the plugin code that uses the patch.
- **Never reformat, rename or tidy up upstream code.** It keeps upstream's style, so merges stay clean. Our C++ style rules don't apply here.
- **This repo is public.** No secrets, keys, anticheat logic, plugin code or private backend details.

## Commands

- Build and test with the plugin: in `../anvil-plugin`, after moving its submodule to your commit. Its `CLAUDE.md` has the commands. The local stack in `../anvil/infra/` builds from there.
- Update from upstream: `git fetch upstream`, then `git merge upstream/master`, then build and run the server from anvil-plugin.

## Reference

| File | When to read it |
|---|---|
| `.claude/rules/naming.md` | Loads automatically for code files: how to choose names, and when a comment is worth writing |
| `../anvil/docs/glossary.md` | The agreed name for every domain concept (it lives in Anvil-CJ/anvil). Check it before naming one |
| `README.md` | Upstream's build and server setup instructions |
| `../anvil-plugin/docs/plugin-api.md` | Before an engine patch: what the plugin API can reach, and its traps |

## Keeping this file small

Only rules that apply to every task in this repo belong here. Details go in separate docs; add a row to the table above instead of a new section.
