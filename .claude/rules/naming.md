---
paths:
  - "**/*.{cc,cpp,cxx,h,hpp,hxx,inl,c,gsc,ts,tsx,js,jsx,py,sql,sh,ps1,cs,go,rs}"
---

# Naming, in every language

This file is shared across all four Anvil-CJ repos, and the master copy is in Anvil-CJ/anvil. Casing rules live in each language's rule file (`cpp.md`, `gsc.md`, `backend-web.md`); this file is about choosing the words. In cod4x-server, upstream code keeps its own names, so never rename upstream symbols.

A reader should know what a type is, or what a function does, from its name alone, without opening it.

## Choosing the words

The examples use C++ casing.

| Kind | Rule | Good | Bad |
|---|---|---|---|
| Types | A noun for what it is | `RunTimer`, `CheckpointList`, `SpeedometerHud` | `RunManager`, `HudData`, `CheckpointHelper` |
| Functions that do something | Start with a verb | `StartRun`, `SubmitRun`, `LoadPosition` | `Run`, `Checkpoint`, `HandleStuff` |
| Functions that only return a value | Name the value | `ElapsedMs()`, `NearestCheckpoint()` | `DoCalc()`, `GetIt()` |
| Booleans, and functions that return bool | Ask a yes/no question | `is_paused`, `has_finished`, `CanSavePosition()` | `paused_flag`, `status`, `Check()` |
| Values with a unit | Put the unit in the name | `elapsed_ms`, `speed_ups`, `max_fps` | `time`, `speed`, `t` |
| Collections | Plural, or describe the lookup | `checkpoints`, `runs_by_player` | `checkpoint_list_array`, `map` |
| Events and callbacks | `On` plus what happened | `OnRunFinished`, `OnPlayerConnected` | `RunCallback`, `Event1` |

## Length: balanced

- Aim for one to three words, and rarely more than four. A name should be long enough to make sense outside its file and short enough to read at a glance.
- Match the length to the scope. `i` is fine in a three-line loop, but a class member or a public function needs a full name.
- Don't repeat what the context already says: `run::Timer`, not `run::RunTimer`; `player.name`, not `player.player_name`.
- No Java-style chains like `AbstractCheckpointValidationStrategyFactory`. If a name needs that many words, the design is too complicated.

## Words to avoid

- **Filler words that say nothing:** Manager, Helper, Util, Data, Info, Object, Thing, Handler, Process, Do. If you reach for one of these, the name isn't finished yet. Say what the thing holds or does.
- **Made-up abbreviations** like `cpMgr` or `plyrSt`. Use only abbreviations that every CoD player or programmer knows: `fps`, `hud`, `id`, `ms`, `ups`, `pb`, `wr`, `tas`, `url`.
- **"Server" on its own,** because it's ambiguous. Say `game_server` or `backend`.
- **Vague or numbered names** like `data2`, `temp` or `new_value`, except in tiny scopes.

## Consistency

- **One name per concept, everywhere:** across files, languages and repos. A run is a `run` in GSC, C++, SQL and on the website, never also an "attempt" or a "session".
- **Domain terms come from the glossary** at `docs/glossary.md` in Anvil-CJ/anvil (`../anvil/docs/glossary.md` in the local workspace).
  - Check it before you name a domain concept.
  - If the concept is new, add it to the glossary in the same change.
  - If an existing name is wrong, rename it everywhere instead of adding a second name.
- **Follow the patterns around you.** If neighboring code uses `Load…` and `Save…`, don't add `Fetch…` or `Persist…`.
- **Use matching opposites:** start/stop, begin/end, open/close, load/save, enable/disable, add/remove. Don't mix halves of different pairs, like start/end.
