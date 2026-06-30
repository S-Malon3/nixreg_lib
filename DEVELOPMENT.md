# Development Environment

## ESP-IDF Setup (Arch Linux)
Install the AUR package, then run one-time installer:
```bash
/opt/esp-idf/install.sh
```
or if using fish shell
```fish
/opt/esp-idf/install.fish
``` 
Source manually in any terminal session where ESP-IDF is required
```bash
source /opt/esp-idf/export.sh
```

Fish shell:
```fish
source /opt/esp-idf/export.fish
```

## Desktop builds
Requires GCC16.1.1+/Clang 22.1.6+, CMake 4.3.4+, and Boost.Test 1.9q+. On Arch:
```bash
sudo pacman -S cmake boost
```

## Running Tests
```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Commit Conventions

This project uses [Conventional Commits](https://www.conventionalcommits.org), with one addition: `wip:` is permitted for local, in-progress commits

**Allowed types:** `feat`, `fix`, `docs`, `style`, `refactor`, `perf`, `test`, 
`build`, `ci`, `chore`, `revert`, `wip`

### `wip:` commits

`wip:` commits are for local checkpointing only and can not be pushed to `origin`.  Before Pushing, squash or fold all `wip:` commits into the meaninful commit(s) they belong to via interactive rebase

```bash
git rebase -i origin/main
```

In the rebase editor, mark `wip:` commits as `squash` (or `fixup` to discard 
their message) and leave properly-typed commits as `pick`:

```
squash wip: doing a thing
squash wip: did more for the thing
pick   feat: the thing
squash wip: making the thing better
pick   perf: improved thing
```

A `pre-push` hook will reject pushes containing `wip:` commits as a safety net.

### Setup

After cloning, install git hooks once:
```bash
./scripts/install-hooks.sh
```

This installs:
- `commit-msg` — validates commit messages against Conventional Commits via commitlint
- `pre-push` — blocks pushes containing unsquashed `wip:` commits
