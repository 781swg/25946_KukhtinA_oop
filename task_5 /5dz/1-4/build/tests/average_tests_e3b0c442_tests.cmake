add_test([=[AverageTests.NormalNumbers]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests/average_tests]==] [==[--gtest_filter=AverageTests.NormalNumbers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AverageTests.NormalNumbers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/25946_KukhtinA_oop/task_5 /5dz/1-4/tests/test_average.cpp:6]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AverageTests.NegativeNumbers]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests/average_tests]==] [==[--gtest_filter=AverageTests.NegativeNumbers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AverageTests.NegativeNumbers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/25946_KukhtinA_oop/task_5 /5dz/1-4/tests/test_average.cpp:11]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RandomTests.ResultInExpectedRange]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests/average_tests]==] [==[--gtest_filter=RandomTests.ResultInExpectedRange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RandomTests.ResultInExpectedRange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/25946_KukhtinA_oop/task_5 /5dz/1-4/tests/test_average.cpp:15]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FailureDemo.Expect]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests/average_tests]==] [==[--gtest_filter=FailureDemo.DISABLED_Expect]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FailureDemo.Expect]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/25946_KukhtinA_oop/task_5 /5dz/1-4/tests/test_average.cpp:22]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FailureDemo.Assert]=]  [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests/average_tests]==] [==[--gtest_filter=FailureDemo.DISABLED_Assert]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FailureDemo.Assert]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ÐÐÐ/25946_KukhtinA_oop/task_5 /5dz/1-4/tests/test_average.cpp:27]==]
    WORKING_DIRECTORY [==[/Users/alekseikuhtin/Desktop/NSU 2 course/ООП/25946_KukhtinA_oop/task_5 /5dz/1-4/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(average_tests_TESTS [==[AverageTests.NormalNumbers]==] [==[AverageTests.NegativeNumbers]==] [==[RandomTests.ResultInExpectedRange]==] [==[FailureDemo.Expect]==] [==[FailureDemo.Assert]==])
