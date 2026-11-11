# How we work (all Anvil-CJ repos)

Shared: identical copies live in anvil, anvil-plugin, client, anticheat and cod4x-server, with the master in anvil, so change all five together. It loads in every session, so it holds only rules for every task.

## Principles

- **Performance is a requirement.** Measure hot code; never guess how fast it is.
- **Easy to maintain, extend and reuse:** small units with one job and clear interfaces; reuse or extract code instead of copying it; no abstractions for imagined future needs.
- **Quality beats delivery speed.** Never cut corners quietly; say what the tradeoff is.
- **Input from game clients, the network and files is hostile** until it's validated.

## Every change

1. **Understand** the code, its callers and the relevant docs. Don't guess.
2. **Plan** anything bigger than a small fix, and get agreement before writing code. In a batch, the agreed list is that agreement. Trivial changes (a typo, a comment) skip this.
3. **Implement** in small steps, following the language rules in `.claude/rules/`.
4. **Verify:** build with warnings as errors, run the tests and run the program. New behavior gets tests; every bug fix gets a regression test.
5. **Attack it:** list the ways it could fail (bad input, edge cases, error paths, concurrency, hot-path cost, security) and check each one yourself.
6. **Report** in plain language: what changed, the commands you ran and their results, what the attack and any review found, and the remaining risks.

**Depth follows risk.** Hot code, the anticheat and anything a player could abuse get every step in full. Tools, scripts and docs get a quick attack on the obvious failures. Break a fix on purpose to see its test fail only where a silent bug would be expensive. Never cut tests for new behavior, warning-free builds, or in-game checks for what tests can't show.

**Done** means: it builds without warnings, the tests pass, it's formatted, it went through step 5 (and a review where one is required), and the docs are updated. Say exactly what couldn't be verified.

## Batches

Work in batches of 5 to 10 features. Agree on the list once, then build it without stopping to ask; pick sensible defaults and list them in the report. One agent at a time, one feature after another, so nothing is researched or written twice. The user tests a batch in one game session, from a checklist of what the tests can't show.

## Independent review

Once per feature, after the user has confirmed in game that it works (not after each round of fixes), spawn the `reviewer` subagent if the feature touches hot code (per frame, usercmd or server frame), the anticheat, network or security boundaries, database migrations, or more than about 200 lines. Do it before the feature's PR merges, or in the current phase after its commits land.
- Give it the goal, the diff of all the feature's commits, how to build and test, and the builds and tests already run with their results. Not your opinion of the code.
- Without the subagent, give a general-purpose subagent `.claude/agents/reviewer.md`.
- Confirm each finding, fix it and verify again. After critical or major findings, send the fixes back to the same reviewer.

## Never

- Claim something works without running it and seeing it work.
- Weaken or skip tests, or disable warnings, to get a passing result.
- Present stubs, TODOs or a "simplified version" as finished work.
- Push more than a small change straight to the default branch, or force-push it.
- Add a dependency without asking first: say its license, cost and whether it's maintained. MIT and closed-source repos take permissive licenses only.
- Copy code from other projects (OpenCJ, other mods, forums). Read them for ideas and write our own.
- Commit or print secrets.

## Git

**Current phase: veteri and calzum push every change straight to the default branch. Rebase onto the latest default branch before you push, and never force-push it.**

Commit messages: an imperative summary line under 72 characters, then a body that explains why. What counts as a small change, PR branches, and review and merge are in `docs/git.md` in the anvil repo: read it before opening a PR.

## Working with the maintainers

Not everyone here is a programmer. Explain in plain words first, give a recommendation instead of an open technical question, and push back when a request would hurt quality: "just make it work" doesn't override these rules.
