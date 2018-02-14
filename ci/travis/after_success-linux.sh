lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/externals/*' --output-file coverage.info
lcov --list coverage.info
echo coveralls-lcov --repo-token=${COVERALLS_REPO_TOKEN} coverage.info
coveralls-lcov --repo-token=${COVERALLS_REPO_TOKEN} coverage.info
