#include "../src/text_analyzer.hpp"
#include "gtest/gtest.h"
#include <iostream>

// To use a test fixture, derive a class from testing::Test.
struct TextAnalyzerTest : testing::Test {
    protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
        std::cout << "setting up" << std::endl;

        std::ifstream text_file;
        text_file.open("~/Dropbox/CSC/Practice/I/se_engine/small_text_correct.txt", std::ios_base::binary);
        analyzer_ = new text_analyzer(text_file);
    }


    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }

    // Declares the variables your tests want to use.
    text_analyzer* analyzer_;
};

// When you have a test fixture, you define a test using TEST_F
// instead of TEST.

TEST_F(TextAnalyzerTest, TestFirstFoundPreposition) {

    EXPECT_EQ("on", analyzer_->get_found_preposition(0));
}
