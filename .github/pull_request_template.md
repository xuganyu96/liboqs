<!-- Please give a brief explanation of the purpose of this pull request. -->

<!-- Does this PR resolve any issue?  If so, please reference it using automatic-closing keywords like "Fixes #123." -->

<!-- Any PR adding a new feature is expected to contain a test; the test should be part of CI testing, preferably within the ".github/workflows" directory tree. Please add an explanation to the PR if/when (why) this cannot be done. -->

<!-- Please answer the following questions to help manage version and changes across projects. -->

* [ ] Does this PR change the input/output behaviour of a cryptographic algorithm (i.e., does it change known answer test values)?  (If so, a version bump will be required from *x.y.z* to *x.(y+1).0*.)
* [ ] Does this PR change the list of algorithms available -- either adding, removing, or renaming? Does this PR otherwise change an API? (If so, PRs in fully supported downstream projects dependent on these, i.e., [oqs-provider](https://github.com/open-quantum-safe/oqs-provider) will also need to be ready for review and merge by the time this is merged. Also, make sure to update the list of algorithms in the continuous benchmarking files: .github/workflows/kem-bench.yml and sig-bench.yml)

### AI disclosure

<!-- Follow the AI Policy in CONTRIBUTING.md: https://github.com/open-quantum-safe/liboqs/blob/main/CONTRIBUTING.md#ai-policy
Write this description yourself; AI translation or grammar edits of your own text are permitted and must be disclosed.
If no generative AI was used, write "None" below. Otherwise, identify the tools and models used (or say "unknown"), explain how they were used, and identify the affected files or sections. Include AI-assisted review or investigation and translation or grammar edits of this PR description.
Confirm that you have reviewed and verified the contribution, and describe any relevant testing.

For each commit containing AI-assisted changes, add an Assisted-By: <tool>:<model> trailer after a blank line at the end of the commit message. Examples:
Assisted-By: claude-code:claude-sonnet-4-5
Assisted-By: cursor:unknown
Use the reported model identifier, or "unknown" if unavailable. Add one trailer per tool/model combination and preserve them when rebasing or squashing.
Use Assisted-By instead of Co-Authored-By for all AI contributions. AI use limited to this description requires disclosure here but no trailer on otherwise unaided commits.
-->

AI use:

<!-- Once your pull request is ready for review and passing continuous integration tests, please convert from a draft PR to a normal PR, and request a review from one of the OQS core team members. -->
