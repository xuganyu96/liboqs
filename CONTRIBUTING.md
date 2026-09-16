# Contributing

The OQS core team welcomes all proposals to improve this project. This may take 
the form of [a discussion](https://github.com/open-quantum-safe/liboqs/discussions)
for input or feedback, possible bug reports or feature requests via [issues](https://github.com/open-quantum-safe/liboqs/issues)
as well as new code and documentation via a [pull request (PR)](https://github.com/open-quantum-safe/liboqs/pulls).

## Baseline design goal

OQS is a collection of many different PQC algorithms, maintained by a small team of people who are not guaranteed to be versed in the intricate details of each algorithm.

Therefore, all contributions to the general logic of the project should be as independent of any single algorithm such as to ease long-term maintainability. If changes are contributed catering to the properties of a specific algorithm, it is expected that consideration is given at least how the other algorithms of the same type (KEM or SIG) should cater to the proposed changes, e.g., by way of a new, generally satisfiable API.

All contributions to a specific algorithm ideally come with the willingness to provide long-term support, or at least a contact person that can help the OQS team pinpoint potential problems with the algorithm.

## Review and Feedback

We aim to provide timely feedback to any input. If you are uncertain as to whether
a particular contribution is welcome, needed or timely, please first open an [issue](https://github.com/open-quantum-safe/liboqs/issues)
particularly in case of possible bugs or new feature requests or create a
[discussion](https://github.com/open-quantum-safe/liboqs/discussions).

## Pull requests

Pull requests should clearly state their purpose, possibly referencing an existing
[issue](https://github.com/open-quantum-safe/liboqs/issues) when resolving it.

Contributions made with generative AI must follow the [AI Policy](#ai-policy),
including its disclosure and commit trailer requirements.

All PRs should move to "Ready for Review" stage only if all CI tests pass (are green).

The OQS core team is happy to provide feedback also to Draft PRs in order to improve
them before the final "Review" stage.

### Coding style

This project has adopted a slightly modified [Google code formatting style](https://astyle.sourceforge.net/astyle.html#_style=google) for the core components
of the library as documented in the [style template](.astylerc).
The `astyle` tool is used to check formatting in CI.
Due to variations in behaviour across version and platforms, it is possible to encounter CI failures even if code has been locally formatted with `astyle`.
To assist with this inconvenience, we provide a convenience script which runs `astyle` in the same Docker image that we use for the CI checks:
```bash
LIBOQS_DIR=<liboqs directory> ./scripts/format_code.sh
```
This script has been tested on x86\_64 Ubuntu and arm64 macOS. Contributions for other platforms are welcome and appreciated!

### Git hooks

This project uses git hooks to automatically run linters and formatters. Git
hooks are stored under `.githooks/`. After cloning this repository, you can
point git to use these hooks by setting `core.hooksPath`:

```bash
git config core.hooksPath .githooks
```

> `core.hooksPath` is available in git 2.9 or newer; for older versions of git,
> please manually set up symlinks or copy the hooks into `.git/hooks`.

### Public and internal APIs

Public API functions are marked with the `OQS_API` keyword. These functions are made available to users of the library.
OQS also has an internal API for common code such as hashing and memory management.
The OQS test programs use this internal API.
These programs link against the `oqs-internal` library, which is built alongside the main library.
The main library also contains the common code, but it does not expose it to external callers.
The internal library is not installed via `ninja install`, and source code should not link against it.

### Continuous Integration (CI)

`liboqs` uses GitHub Actions for CI.
For a comprehensive overview of our CI setup, see [CI.md](CI.md).

#### Running CI on your branch

OQS attempts to be responsible with resource usage and only runs a minimal set of tests automatically on push.
A more thorough test suite runs automatically on pull requests.
To trigger these tests before creating a PR, include the string "[full tests]" in a commit message.
Other trigger strings are documented in [CI.md](CI.md#push.yml).

#### Running CI locally

[Act](https://github.com/nektos/act) is a tool facilitating local execution of
GitHub CI jobs. When executed in the main `liboqs` directory, 

    act -l Displays all GitHub CI jobs
    act -j some-job Executes "some-job"

When installing `act` as a GitHub extension, prefix the commands with `gh `.

## Modifications to CI

Modifications to GitHub Actions workflows are checked with [actionlint](https://github.com/rhysd/actionlint) during the [basic.yml](.github/workflows/basic.yml) job, protecting the CI chain and against wrong approval decisions based on improper CI runs.  Changes to these workflows can be validated locally with `actionlint`:

```bash
actionlint .github/workflows/*.yml
```

or running the CI locally (as above):

```bash
act workflow_call -W '.github/workflows/basic.yml'
```

### New features

Any PR introducing a new feature is expected to contain a test of this feature
and this test should be part of the CI pipeline.

## AI Policy

AI-assisted contributions, including work performed by AI agents, are welcome.
All contributions must meet the same quality standards, and contributors remain
responsible for everything they submit. Maintainers may request clarification
or close submissions that do not comply with this policy.

### Disclosure

Contributions containing code, documentation, or other text produced with the
help of generative AI must disclose that use in the pull request description.
Identify the tools used, explain how they were used, and identify the affected
files or sections. The same disclosure requirement applies to issues and
security reports, including AI-assisted investigation and permitted translation
or grammar edits. Follow the communication rules below when writing these
descriptions and reports.

For each commit containing AI-assisted changes, add an
`Assisted-By: <tool>:<model>` trailer after a blank line at the end of the commit
message. For example:

```text
Assisted-By: claude-code:claude-sonnet-4-5
Assisted-By: cursor:unknown
```

Use the model identifier reported by the tool, or `unknown` if unavailable.
Add one trailer per tool/model combination and preserve them when rebasing or
squashing. Use `Assisted-By` instead of `Co-Authored-By` for all AI contributions;
reserve `Co-Authored-By` for human co-authors.

Trailers supplement the PR disclosure. AI use limited to the PR description
requires disclosure there, but no trailer on otherwise unaided commits.

### Responsibility

Contributors must review and verify all AI-assisted contributions before
submission, including running appropriate tests for code changes. They must
understand and be able to explain their changes and the existing code relevant
to those changes. Maintainers may reject submissions that contributors cannot
explain or substantiate.

### Communication

Write pull request descriptions, issue descriptions, security reports, and
discussion or review comments yourself. AI may be used to translate or correct
the grammar of your own text, but not to generate its substance. Review any
such edits to ensure that they preserve your meaning and voice. When using AI
for translation, consider including your original text followed by the
translation in a block quote, labelled as an AI translation.

This restriction applies to communication with maintainers; AI-assisted source
code comments and project documentation are permitted under the disclosure and
verification requirements above.

### Licensing

Contributors are responsible for ensuring that AI-assisted contributions comply
with applicable copyright and licensing requirements, including any required
attribution and license notices.

### Security

Follow [SECURITY.md](SECURITY.md) when reporting potential vulnerabilities.
Security researchers and automated agents should also follow
[.github/AGENTS.md](.github/AGENTS.md) and consult the
[threat model](.github/THREAT_MODEL.md) for investigation and reporting guidance.
Contributors using AI assistants are encouraged to read OpenSSF's
[Security-Focused Guide for AI Code Assistant Instructions](https://best.openssf.org/Security-Focused-Guide-for-AI-Code-Assistant-Instructions).

## Failsafe

If you feel your contribution is not getting proper attention, please be sure to
add a tag to one or more of our [most active contributors](https://github.com/open-quantum-safe/liboqs/graphs/contributors).

## Issues to start working on

If you feel like contributing but don't know what specific topic to work on,
please check the [open issues tagged "good first issue" or "help wanted"](https://github.com/open-quantum-safe/liboqs/issues).

You can also take a look at the [contribution wishlist](https://github.com/open-quantum-safe/liboqs/wiki/Contribution-wishlist) for more substantial contributions we are interested in.
