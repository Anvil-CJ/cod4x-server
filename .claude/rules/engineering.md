# How we work (all Anvil-CJ repos)

This file is shared. Identical copies live in the anvil, client, anticheat and cod4x-server repos, and the master copy is in Anvil-CJ/anvil, so change all four together. It loads in every session: keep it to rules that apply to every task.

## Principles

- **Performance is a requirement.** Measure hot code; never guess how fast it is.
- **Code must be easy to maintain, extend and reuse:**
  - small units that each do one job, with clear interfaces
  - no duplication: reuse or extract existing code instead of copying it
  - no abstractions built only for imagined future needs
- **Quality beats delivery speed.** Never cut corners quietly; say what the tradeoff is.
- **Treat everything from game clients, the network and files as hostile** until it's validated.

## Every change

1. **Understand.** Read the code, its callers and the relevant docs. Don't guess.
2. **Plan** anything bigger than a small fix, and get agreement before writing code.
3. **Implement** in small steps, following the language rules in `.claude/rules/`.
4. **Verify.** Build with warnings as errors, run the tests, and run the program. New behavior gets tests, and every bug fix gets a regression test.
5. **Attack it.** List the ways it could fail (bad input, edge cases, error paths, concurrency, hot-path performance, security) and check each one yourself. This costs little, so do it for every change.
6. **Report** in plain language: what changed, how you verified it (the commands and their results), what the attack and any review found, and what risks remain.

Trivial changes, such as a typo or a comment, skip step 2.

**Done** means: it builds without warnings, the tests pass, it's formatted, it has gone through step 5 (plus a review where one is required), and the docs are updated. If something couldn't be verified, say exactly what.

## Independent review before a PR

Spawn the `reviewer` subagent once before opening a pull request, but only if the PR touches any of these:
- hot code (per frame, per usercmd, per server frame)
- the anticheat
- network or security boundaries
- database migrations
- more than about 200 changed lines

How to run it:
- Give it the goal, the diff and how to build and test. Don't give it your opinion of the code.
- If the subagent isn't available, give a general-purpose subagent the instructions in `.claude/agents/reviewer.md`.
- Confirm each finding, fix it, and verify again.
- Run the reviewer a second time only if it found critical or major problems.

## Never

- Claim something works without running it and seeing it work.
- Weaken or skip tests, or disable warnings, to get a passing result.
- Present stubs, TODOs or a "simplified version" as finished work.
- Push anything except a small change (defined under Git) straight to the default branch.
- Force-push the default branch.
- Add a dependency without asking first. Explain its license, its cost and whether it's maintained. Repos that are MIT or closed source take permissive licenses only.
- Copy code from other projects (OpenCJ, other mods, forums). Read them for ideas, and write our own code.
- Commit or print secrets.

## Git

**Current phase: only veteri works in these repos, so every change goes straight to the default branch. When a second person starts, delete this line.**

- **Small changes go straight to the default branch.** A change is small only if all of these are true:
  - it's a few lines (roughly under 30)
  - it doesn't touch hot code, the anticheat, network or security boundaries, database migrations, `contracts/` or the build setup
  - it builds and the tests pass
- **Everything else goes through a pull request.** When in doubt, it's a PR.
- **PR branches:**
  - one short-lived branch per task, started from the latest default branch
  - small enough to merge within a day or two
  - rebased onto the latest default branch before you open the PR, and again before it's merged
  - on your own task branch, `git push --force-with-lease` after a rebase is fine
- **Never start a branch from another unmerged branch.** If the work needs something unmerged, get that merged first, or split the shared part into its own small PR.
- **Unfinished features can be merged** if they're switched off behind a setting, so branches never need to live long.
- **Opening a PR:**
  - push the branch and open the PR with `gh pr create`
  - write the description in plain language: what changed and why, how it was verified, and what the review found
  - give the person you're working with the PR link
- **Review and merge:**
  - veteri reviews every PR, and PRs are squash-merged
  - don't merge your own PR unless veteri tells you to
  - when review comments arrive, read them with `gh`, fix them on the same branch and push
- **Commit messages:** an imperative summary line under 72 characters, then a body that explains why.

## Working with the maintainers

Not everyone here is a programmer.
- Explain in plain words first.
- Give a recommendation instead of asking an open technical question.
- Push back when a request would hurt quality. "Just make it work" doesn't override these rules.
