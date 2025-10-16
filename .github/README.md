# Bungee: Audio time and pitch library

This is Ableton's fork of https://github.com/bungee-audio-stretch/bungee.

[Bungee's original README](../README.md)

## Versioning scheme

Patches are tracked on trunk-like Ableton release branches that follow the
naming scheme `ableton/vX.Y.Z`. They're named after the Bungee release version
they're based on, e.g. `ableton/v2.3.26`. It's prohibited to rewrite or delete
such branches to prevent breaking the history of repositories that have a
bungee.git submodule.

The latest Ableton release branch is set as the default branch for convenience.

## How to update

### Adding a patch

Create a pull request targeting the current default branch, aka the latest
Ableton release branch.

### Update to a new Bungee release

- Create a new Ableton release branch based on the new Bungee release, e.g.
  `ableton/v2.4.0` and push it.
- Create a pull request targeting the newly created Ableton release branch.
- Add the required patches by rebasing the additional commits of the previous
  Ableton release branch and resolve any conflicts if they occur.
- Add any newly required patches as commits to the PR.
- Merge the PR.
- Ask the maintainers to update the default branch.
