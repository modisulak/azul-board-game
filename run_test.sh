#!/bin/bash
TEST_INPUTS=resources/tests
TEST_OUTPUTS=save_files/save_tests

if [[ -z "$4" || "$4" == "null" ]]; then
  OUTPUT=/dev/null
else
  OUTPUT="${TEST_OUTPUTS}/${3}_${4}.txt"
fi

./"${1}/${2}" < "${TEST_INPUTS}/${3}/${3}_player.txt" > "${OUTPUT}"

if (diff "${TEST_INPUTS}/${3}/${3}_expected.txt" "${TEST_OUTPUTS}/${3}_output.txt"); then
  echo "Passed!"
else
  echo "Failed :("
fi
