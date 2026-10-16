add_test([=[AverageTests.Integers]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests/average_tests]==] [==[--gtest_filter=AverageTests.Integers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AverageTests.Integers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/5dz/5/tests/test_average.cpp:6]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AverageTests.Doubles]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests/average_tests]==] [==[--gtest_filter=AverageTests.Doubles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AverageTests.Doubles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/5dz/5/tests/test_average.cpp:11]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RandomTests.IntegersInRange]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests/average_tests]==] [==[--gtest_filter=RandomTests.IntegersInRange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RandomTests.IntegersInRange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/5dz/5/tests/test_average.cpp:15]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RandomTests.DoublesInRange]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests/average_tests]==] [==[--gtest_filter=RandomTests.DoublesInRange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RandomTests.DoublesInRange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/5dz/5/tests/test_average.cpp:21]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FailureDemo.Expect]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests/average_tests]==] [==[--gtest_filter=FailureDemo.DISABLED_Expect]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FailureDemo.Expect]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/5dz/5/tests/test_average.cpp:27]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FailureDemo.Assert]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests/average_tests]==] [==[--gtest_filter=FailureDemo.DISABLED_Assert]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FailureDemo.Assert]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/5dz/5/tests/test_average.cpp:32]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/5dz/5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(average_tests_TESTS [==[AverageTests.Integers]==] [==[AverageTests.Doubles]==] [==[RandomTests.IntegersInRange]==] [==[RandomTests.DoublesInRange]==] [==[FailureDemo.Expect]==] [==[FailureDemo.Assert]==])
