if(EXISTS "/mnt/c/Users/Max/Downloads/oop6/build/test/BalagurFate3EditorTests[1]_tests.cmake")
  include("/mnt/c/Users/Max/Downloads/oop6/build/test/BalagurFate3EditorTests[1]_tests.cmake")
else()
  add_test(BalagurFate3EditorTests_NOT_BUILT BalagurFate3EditorTests_NOT_BUILT)
endif()
