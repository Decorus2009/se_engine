#include "../src/text_analyzer.hpp"
#include <gtest/gtest.h>
#include <iostream>

// To use a test fixture, derive a class from testing::Test.
struct TextAnalyzerTest : testing::Test {
    protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
        //std::cout << "setting up!" << std::endl;

        std::ifstream text_file;
        text_file.open("small_text_correct.txt", std::ios_base::binary);
        if( text_file.is_open() ) {
            //std::cout << "File Opened." << "\n";
            analyzer_ = new text_analyzer(text_file, "-en");
            logger log("DEBUG");
            analyzer_->analyze(log);
        }
        else {
            std::cout << "Error: file not found." << "\n";
            throw 5;
        }
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

TEST_F(TextAnalyzerTest, TestFoundPrepositions)
{
    EXPECT_EQ("on", analyzer_->get_preposition(0));
    EXPECT_EQ("to", analyzer_->get_preposition(1));
    EXPECT_EQ("on", analyzer_->get_preposition(2));
    EXPECT_EQ("of", analyzer_->get_preposition(3));
    EXPECT_EQ("on", analyzer_->get_preposition(4));
    EXPECT_EQ("but", analyzer_->get_preposition(5));
    EXPECT_EQ("on", analyzer_->get_preposition(6));
    EXPECT_EQ("at", analyzer_->get_preposition(7));
    EXPECT_EQ("or", analyzer_->get_preposition(8));
    EXPECT_EQ("at", analyzer_->get_preposition(9));
    EXPECT_EQ("as", analyzer_->get_preposition(10));
    EXPECT_EQ("down", analyzer_->get_preposition(11));
    EXPECT_EQ("in", analyzer_->get_preposition(12));
    EXPECT_EQ("to", analyzer_->get_preposition(13));
    EXPECT_EQ("with", analyzer_->get_preposition(14));
    EXPECT_EQ("as", analyzer_->get_preposition(15));
    EXPECT_EQ("through", analyzer_->get_preposition(16));
    EXPECT_EQ("to", analyzer_->get_preposition(17));
    EXPECT_EQ("to", analyzer_->get_preposition(18));
    EXPECT_EQ("in", analyzer_->get_preposition(19));
    EXPECT_EQ("in", analyzer_->get_preposition(20));

    EXPECT_EQ("as far as", analyzer_->get_preposition(21));
    EXPECT_EQ("to", analyzer_->get_preposition(22));
    EXPECT_EQ("ago", analyzer_->get_preposition(23));
    EXPECT_EQ("in", analyzer_->get_preposition(24));
    EXPECT_EQ("away", analyzer_->get_preposition(25));
    EXPECT_EQ("in", analyzer_->get_preposition(26));
    EXPECT_EQ("into", analyzer_->get_preposition(27));
    EXPECT_EQ("into", analyzer_->get_preposition(28));
    EXPECT_EQ("into", analyzer_->get_preposition(29));

    EXPECT_EQ("by", analyzer_->get_preposition(30));
    EXPECT_EQ("in", analyzer_->get_preposition(31));
    EXPECT_EQ("onto", analyzer_->get_preposition(32));
    EXPECT_EQ("beneath", analyzer_->get_preposition(33));
    EXPECT_EQ("into", analyzer_->get_preposition(34));
    EXPECT_EQ("at", analyzer_->get_preposition(35));
    EXPECT_EQ("among", analyzer_->get_preposition(36));
    EXPECT_EQ("away", analyzer_->get_preposition(37));
    EXPECT_EQ("to", analyzer_->get_preposition(38));
    EXPECT_EQ("amidst", analyzer_->get_preposition(39));
    EXPECT_EQ("round", analyzer_->get_preposition(40));
    EXPECT_EQ("beyond", analyzer_->get_preposition(41));
    EXPECT_EQ("like", analyzer_->get_preposition(42));
    EXPECT_EQ("minus", analyzer_->get_preposition(43));
    EXPECT_EQ("nearest", analyzer_->get_preposition(44));
    EXPECT_EQ("outside", analyzer_->get_preposition(45));
    EXPECT_EQ("since", analyzer_->get_preposition(46));
    EXPECT_EQ("throughout", analyzer_->get_preposition(47));
    EXPECT_EQ("versus", analyzer_->get_preposition(48));
}


TEST_F(TextAnalyzerTest, TestFoundRequests)
{
    // On the whole
    EXPECT_EQ("On the whole", analyzer_->get_request(0));

    // he was to be congratulated
    EXPECT_EQ("was to", analyzer_->get_request(1));
    EXPECT_EQ("he was to", analyzer_->get_request(2));
    EXPECT_EQ("to be", analyzer_->get_request(3));
    EXPECT_EQ("to be congratulated", analyzer_->get_request(4));
    EXPECT_EQ("was to be", analyzer_->get_request(5));
    EXPECT_EQ("he was to be congratulated", analyzer_->get_request(6));

    // be congratulated on his idea
    EXPECT_EQ("congratulated on", analyzer_->get_request(7));
    EXPECT_EQ("be congratulated on", analyzer_->get_request(8));
    EXPECT_EQ("on his", analyzer_->get_request(9));
    EXPECT_EQ("on his idea", analyzer_->get_request(10));
    EXPECT_EQ("congratulated on his", analyzer_->get_request(11));
    EXPECT_EQ("be congratulated on his idea", analyzer_->get_request(12));

    // his idea of hiding here
    EXPECT_EQ("idea of", analyzer_->get_request(13));
    EXPECT_EQ("his idea of", analyzer_->get_request(14));
    EXPECT_EQ("of hiding", analyzer_->get_request(15));
    EXPECT_EQ("of hiding here", analyzer_->get_request(16));
    EXPECT_EQ("idea of hiding", analyzer_->get_request(17));
    EXPECT_EQ("his idea of hiding here", analyzer_->get_request(18));

    // comfortable lying on the hot
    EXPECT_EQ("lying on", analyzer_->get_request(19));
    EXPECT_EQ("comfortable lying on", analyzer_->get_request(20));
    EXPECT_EQ("on the hot", analyzer_->get_request(21));
    EXPECT_EQ("lying on the hot", analyzer_->get_request(22));

    // hard earth but
    EXPECT_EQ("earth but", analyzer_->get_request(23));
    EXPECT_EQ("hard earth but", analyzer_->get_request(24));

    // on the other hand
    EXPECT_EQ("on the other", analyzer_->get_request(25));
    EXPECT_EQ("on the other hand", analyzer_->get_request(26));

    // was glaring at him
    EXPECT_EQ("glaring at", analyzer_->get_request(27));
    EXPECT_EQ("was glaring at", analyzer_->get_request(28));
    EXPECT_EQ("at him", analyzer_->get_request(29));
    EXPECT_EQ("glaring at him", analyzer_->get_request(30));

    // or shooting nasty
    EXPECT_EQ("or shooting", analyzer_->get_request(31));
    EXPECT_EQ("or shooting nasty", analyzer_->get_request(32));

    // nasty questions at him
    EXPECT_EQ("questions at", analyzer_->get_request(33));
    EXPECT_EQ("nasty questions at", analyzer_->get_request(34));
    EXPECT_EQ("at him", analyzer_->get_request(35));
    EXPECT_EQ("questions at him", analyzer_->get_request(36));

    // as had happened
    EXPECT_EQ("as had", analyzer_->get_request(37));
    EXPECT_EQ("as had happened", analyzer_->get_request(38));

    // tried sitting down in the living
    EXPECT_EQ("sitting down", analyzer_->get_request(39));
    EXPECT_EQ("tried sitting down", analyzer_->get_request(40));
    EXPECT_EQ("down in", analyzer_->get_request(41));
    EXPECT_EQ("down in the living", analyzer_->get_request(42));
    EXPECT_EQ("sitting down in", analyzer_->get_request(43));
    EXPECT_EQ("tried sitting down in the living", analyzer_->get_request(44));

    // sitting down in the living room
    EXPECT_EQ("down in", analyzer_->get_request(45));
    EXPECT_EQ("sitting down in", analyzer_->get_request(46));
    EXPECT_EQ("in the living", analyzer_->get_request(47));
    EXPECT_EQ("in the living room", analyzer_->get_request(48));
    EXPECT_EQ("down in the living", analyzer_->get_request(49));
    EXPECT_EQ("sitting down in the living room", analyzer_->get_request(50));

    // living room to watch television
    EXPECT_EQ("room to", analyzer_->get_request(51));
    EXPECT_EQ("living room to", analyzer_->get_request(52));
    EXPECT_EQ("to watch", analyzer_->get_request(53));
    EXPECT_EQ("to watch television", analyzer_->get_request(54));
    EXPECT_EQ("room to watch", analyzer_->get_request(55));
    EXPECT_EQ("living room to watch television", analyzer_->get_request(56));

    // watch television with his aunt
    EXPECT_EQ("television with", analyzer_->get_request(57));
    EXPECT_EQ("watch television with", analyzer_->get_request(58));
    EXPECT_EQ("with his", analyzer_->get_request(59));
    EXPECT_EQ("with his aunt", analyzer_->get_request(60));
    EXPECT_EQ("television with his", analyzer_->get_request(61));
    EXPECT_EQ("watch television with his aunt", analyzer_->get_request(62));

    // Almost as though this
    EXPECT_EQ("Almost as", analyzer_->get_request(63));
    EXPECT_EQ("as though", analyzer_->get_request(64));
    EXPECT_EQ("as though this", analyzer_->get_request(65));
    EXPECT_EQ("Almost as though", analyzer_->get_request(66));

    // had fluttered through the open window
    EXPECT_EQ("fluttered through", analyzer_->get_request(67));
    EXPECT_EQ("had fluttered through", analyzer_->get_request(68));
    EXPECT_EQ("through the open", analyzer_->get_request(69));
    EXPECT_EQ("through the open window", analyzer_->get_request(70));
    EXPECT_EQ("fluttered through the open", analyzer_->get_request(71));
    EXPECT_EQ("had fluttered through the open window", analyzer_->get_request(72));

    // Glad to see the boy
    EXPECT_EQ("Glad to", analyzer_->get_request(73));
    EXPECT_EQ("to see", analyzer_->get_request(74));
    EXPECT_EQ("to see the boy's", analyzer_->get_request(75));
    EXPECT_EQ("Glad to see", analyzer_->get_request(76));

    // stopped trying to butt in
    EXPECT_EQ("trying to", analyzer_->get_request(77));
    EXPECT_EQ("stopped trying to", analyzer_->get_request(78));
    EXPECT_EQ("to butt", analyzer_->get_request(79));
    EXPECT_EQ("to butt in", analyzer_->get_request(80));
    EXPECT_EQ("trying to butt", analyzer_->get_request(81));
    EXPECT_EQ("stopped trying to butt in", analyzer_->get_request(82));

    // to butt in
    EXPECT_EQ("butt in", analyzer_->get_request(83));
    EXPECT_EQ("to butt in", analyzer_->get_request(84));

    // Not in the house
    EXPECT_EQ("Not in", analyzer_->get_request(85));
    EXPECT_EQ("in the house", analyzer_->get_request(86));
    EXPECT_EQ("Not in the house", analyzer_->get_request(87));

    // As far as I remember
    EXPECT_EQ("As far as I", analyzer_->get_request(88));
    EXPECT_EQ("As far as I remember", analyzer_->get_request(89));

    // I used to be a jedi
    EXPECT_EQ("used to", analyzer_->get_request(90));
    EXPECT_EQ("I used to", analyzer_->get_request(91));
    EXPECT_EQ("to be", analyzer_->get_request(92));
    EXPECT_EQ("to be a jedi", analyzer_->get_request(93));
    EXPECT_EQ("used to be", analyzer_->get_request(94));
    EXPECT_EQ("I used to be a jedi", analyzer_->get_request(95));

    // long time ago in a galaxy
    EXPECT_EQ("time ago", analyzer_->get_request(96));
    EXPECT_EQ("long time ago", analyzer_->get_request(97));
    EXPECT_EQ("ago in", analyzer_->get_request(98));
    EXPECT_EQ("ago in a galaxy", analyzer_->get_request(99));
    EXPECT_EQ("time ago in", analyzer_->get_request(100));
    EXPECT_EQ("long time ago in a galaxy", analyzer_->get_request(101));

    // time ago in a galaxy far
    EXPECT_EQ("ago in", analyzer_->get_request(102));
    EXPECT_EQ("time ago in", analyzer_->get_request(103));
    EXPECT_EQ("in a galaxy", analyzer_->get_request(104));
    EXPECT_EQ("in a galaxy far", analyzer_->get_request(105));
    EXPECT_EQ("ago in a galaxy", analyzer_->get_request(106));
    EXPECT_EQ("time ago in a galaxy far", analyzer_->get_request(107));

    // far far away
    EXPECT_EQ("far away", analyzer_->get_request(108));
    EXPECT_EQ("far far away", analyzer_->get_request(109));

    // that it’s in the air
    EXPECT_EQ("it’s in", analyzer_->get_request(110));
    EXPECT_EQ("that it’s in", analyzer_->get_request(111));
    EXPECT_EQ("in the air", analyzer_->get_request(112));
    EXPECT_EQ("it’s in the air", analyzer_->get_request(113));

    // into infinity
    EXPECT_EQ("into infinity", analyzer_->get_request(114));

    // fluctuations project into the air
    EXPECT_EQ("project into", analyzer_->get_request(115));
    EXPECT_EQ("fluctuations project into", analyzer_->get_request(116));
    EXPECT_EQ("into the air", analyzer_->get_request(117));
    EXPECT_EQ("project into the air", analyzer_->get_request(118));

    // floating forever into infinity
    EXPECT_EQ("forever into", analyzer_->get_request(119));
    EXPECT_EQ("floating forever into", analyzer_->get_request(120));
    EXPECT_EQ("into infinity", analyzer_->get_request(121));
    EXPECT_EQ("forever into infinity", analyzer_->get_request(122));

    // fluttered by the open
    EXPECT_EQ("fluttered by", analyzer_->get_request(123));
    EXPECT_EQ("by the open", analyzer_->get_request(124));
    EXPECT_EQ("fluttered by the open", analyzer_->get_request(125));

    // fluttered in the open
    EXPECT_EQ("fluttered in", analyzer_->get_request(126));
    EXPECT_EQ("in the open", analyzer_->get_request(127));
    EXPECT_EQ("fluttered in the open", analyzer_->get_request(128));

    // fluttered onto the open
    EXPECT_EQ("fluttered onto", analyzer_->get_request(129));
    EXPECT_EQ("onto the open", analyzer_->get_request(130));
    EXPECT_EQ("fluttered onto the open", analyzer_->get_request(131));

    // fluttered beneath the open
    EXPECT_EQ("fluttered beneath", analyzer_->get_request(132));
    EXPECT_EQ("beneath the open", analyzer_->get_request(133));
    EXPECT_EQ("fluttered beneath the open", analyzer_->get_request(134));

    // fluttered into the open
    EXPECT_EQ("fluttered into", analyzer_->get_request(135));
    EXPECT_EQ("into the open", analyzer_->get_request(136));
    EXPECT_EQ("fluttered into the open", analyzer_->get_request(137));

    // fluttered at the open
    EXPECT_EQ("fluttered at", analyzer_->get_request(138));
    EXPECT_EQ("at the open", analyzer_->get_request(139));
    EXPECT_EQ("fluttered at the open", analyzer_->get_request(140));

    // fluttered among the open
    EXPECT_EQ("fluttered among", analyzer_->get_request(141));
    EXPECT_EQ("among the open", analyzer_->get_request(142));
    EXPECT_EQ("fluttered among the open", analyzer_->get_request(143));

    // fluttered away the open
    EXPECT_EQ("fluttered away", analyzer_->get_request(144));
    EXPECT_EQ("away the open", analyzer_->get_request(145));
    EXPECT_EQ("fluttered away the open", analyzer_->get_request(146));

    // fluttered to the open
    EXPECT_EQ("fluttered to", analyzer_->get_request(147));
    EXPECT_EQ("to the open", analyzer_->get_request(148));
    EXPECT_EQ("fluttered to the open", analyzer_->get_request(149));

    // fluttered amidst the open
    EXPECT_EQ("fluttered amidst", analyzer_->get_request(150));
    EXPECT_EQ("amidst the open", analyzer_->get_request(151));
    EXPECT_EQ("fluttered amidst the open", analyzer_->get_request(152));

    // fluttered round the open
    EXPECT_EQ("fluttered round", analyzer_->get_request(153));
    EXPECT_EQ("round the open", analyzer_->get_request(154));
    EXPECT_EQ("fluttered round the open", analyzer_->get_request(155));

    // fluttered beyond the open
    EXPECT_EQ("fluttered beyond", analyzer_->get_request(156));
    EXPECT_EQ("beyond the open", analyzer_->get_request(157));
    EXPECT_EQ("fluttered beyond the open", analyzer_->get_request(158));

    // fluttered like the open
    EXPECT_EQ("fluttered like", analyzer_->get_request(159));
    EXPECT_EQ("like the open", analyzer_->get_request(160));
    EXPECT_EQ("fluttered like the open", analyzer_->get_request(161));

    // fluttered minus the open
    EXPECT_EQ("fluttered minus", analyzer_->get_request(162));
    EXPECT_EQ("minus the open", analyzer_->get_request(163));
    EXPECT_EQ("fluttered minus the open", analyzer_->get_request(164));

    // fluttered nearest the open
    EXPECT_EQ("fluttered nearest", analyzer_->get_request(165));
    EXPECT_EQ("nearest the open", analyzer_->get_request(166));
    EXPECT_EQ("fluttered nearest the open", analyzer_->get_request(167));

    // fluttered outside the open
    EXPECT_EQ("fluttered outside", analyzer_->get_request(168));
    EXPECT_EQ("outside the open", analyzer_->get_request(169));
    EXPECT_EQ("fluttered outside the open", analyzer_->get_request(170));

    // fluttered since the open
    EXPECT_EQ("fluttered since", analyzer_->get_request(171));
    EXPECT_EQ("since the open", analyzer_->get_request(172));
    EXPECT_EQ("fluttered since the open", analyzer_->get_request(173));

    // fluttered throughout the open
    EXPECT_EQ("fluttered throughout", analyzer_->get_request(174));
    EXPECT_EQ("throughout the open", analyzer_->get_request(175));
    EXPECT_EQ("fluttered throughout the open", analyzer_->get_request(176));

    // fluttered versus the open
    EXPECT_EQ("fluttered versus", analyzer_->get_request(177));
    EXPECT_EQ("versus the open", analyzer_->get_request(178));
    EXPECT_EQ("fluttered versus the open", analyzer_->get_request(179));
}


TEST_F(TextAnalyzerTest, TestFoundRequestsResults)
{
    EXPECT_EQ("On the whole", analyzer_->get_request_result(0).first);
    EXPECT_LE(100, analyzer_->get_request_result(0).second);

    EXPECT_EQ("was to be", analyzer_->get_request_result(1).first);
    EXPECT_LE(100, analyzer_->get_request_result(1).second);

    EXPECT_EQ("congratulated on his", analyzer_->get_request_result(2).first);
    EXPECT_LE(100, analyzer_->get_request_result(2).second);

    EXPECT_EQ("idea of hiding", analyzer_->get_request_result(3).first);
    EXPECT_LE(100, analyzer_->get_request_result(3).second);

    EXPECT_EQ("lying on the hot", analyzer_->get_request_result(4).first);
    EXPECT_LE(100, analyzer_->get_request_result(4).second);

    EXPECT_EQ("hard earth but", analyzer_->get_request_result(5).first);
    EXPECT_LE(100, analyzer_->get_request_result(5).second);

    EXPECT_EQ("on the other hand", analyzer_->get_request_result(6).first);
    EXPECT_LE(100, analyzer_->get_request_result(6).second);

    EXPECT_EQ("glaring at him", analyzer_->get_request_result(7).first);
    EXPECT_LE(100, analyzer_->get_request_result(7).second);

    EXPECT_EQ("or shooting nasty", analyzer_->get_request_result(8).first);
    EXPECT_LE(100, analyzer_->get_request_result(8).second);

    EXPECT_EQ("questions at him", analyzer_->get_request_result(9).first);
    EXPECT_LE(100, analyzer_->get_request_result(9).second);

    EXPECT_EQ("as had happened", analyzer_->get_request_result(10).first);
    EXPECT_LE(100, analyzer_->get_request_result(10).second);

    EXPECT_EQ("sitting down in", analyzer_->get_request_result(11).first);
    EXPECT_LE(100, analyzer_->get_request_result(11).second);

    EXPECT_EQ("down in the living", analyzer_->get_request_result(12).first);
    EXPECT_LE(100, analyzer_->get_request_result(12).second);

    EXPECT_EQ("room to watch", analyzer_->get_request_result(13).first);
    EXPECT_LE(100, analyzer_->get_request_result(13).second);

    EXPECT_EQ("television with his", analyzer_->get_request_result(14).first);
    EXPECT_LE(100, analyzer_->get_request_result(14).second);

    EXPECT_EQ("Almost as though", analyzer_->get_request_result(15).first);
    EXPECT_LE(100, analyzer_->get_request_result(15).second);

    EXPECT_EQ("fluttered through the open", analyzer_->get_request_result(16).first);
    EXPECT_LE(100, analyzer_->get_request_result(16).second);

    EXPECT_EQ("Glad to see", analyzer_->get_request_result(17).first);
    EXPECT_LE(100, analyzer_->get_request_result(17).second);

    EXPECT_EQ("trying to butt", analyzer_->get_request_result(18).first);
    EXPECT_LE(100, analyzer_->get_request_result(18).second);

    EXPECT_EQ("to butt in", analyzer_->get_request_result(19).first);
    EXPECT_LE(100, analyzer_->get_request_result(19).second);

    EXPECT_EQ("Not in the house", analyzer_->get_request_result(20).first);
    EXPECT_LE(100, analyzer_->get_request_result(20).second);



    EXPECT_EQ("As far as I remember", analyzer_->get_request_result(21).first);
    EXPECT_LE(100, analyzer_->get_request_result(21).second);

    EXPECT_EQ("used to be", analyzer_->get_request_result(22).first);
    EXPECT_LE(100, analyzer_->get_request_result(22).second);

    EXPECT_EQ("time ago in", analyzer_->get_request_result(23).first);
    EXPECT_LE(100, analyzer_->get_request_result(23).second);

    EXPECT_EQ("ago in a galaxy", analyzer_->get_request_result(24).first);
    EXPECT_LE(100, analyzer_->get_request_result(24).second);

    EXPECT_EQ("far far away", analyzer_->get_request_result(25).first);
    EXPECT_LE(100, analyzer_->get_request_result(25).second);

    EXPECT_EQ("it’s in the air", analyzer_->get_request_result(26).first);
    EXPECT_LE(100, analyzer_->get_request_result(26).second);

    EXPECT_EQ("into infinity", analyzer_->get_request_result(27).first);
    EXPECT_LE(100, analyzer_->get_request_result(27).second);

    EXPECT_EQ("project into the air", analyzer_->get_request_result(28).first);
    EXPECT_LE(100, analyzer_->get_request_result(28).second);

    EXPECT_EQ("forever into infinity", analyzer_->get_request_result(29).first);
    EXPECT_LE(100, analyzer_->get_request_result(29).second);



    EXPECT_EQ("fluttered by the open", analyzer_->get_request_result(30).first);
    EXPECT_GE(100, analyzer_->get_request_result(30).second);

    EXPECT_EQ("fluttered in the open", analyzer_->get_request_result(31).first);
    EXPECT_GE(100, analyzer_->get_request_result(31).second);

    EXPECT_EQ("fluttered onto the open", analyzer_->get_request_result(32).first);
    EXPECT_GE(50, analyzer_->get_request_result(32).second);

    EXPECT_EQ("fluttered beneath the open", analyzer_->get_request_result(33).first);
    EXPECT_GE(50, analyzer_->get_request_result(33).second);

    EXPECT_EQ("fluttered into the open", analyzer_->get_request_result(34).first);
    EXPECT_GE(100, analyzer_->get_request_result(34).second);

    EXPECT_EQ("fluttered at the open", analyzer_->get_request_result(35).first);
    EXPECT_GE(100, analyzer_->get_request_result(35).second);

    EXPECT_EQ("fluttered among the open", analyzer_->get_request_result(36).first);
    EXPECT_GE(50, analyzer_->get_request_result(36).second);

    EXPECT_EQ("fluttered away the open", analyzer_->get_request_result(37).first);
    EXPECT_GE(50, analyzer_->get_request_result(37).second);

    EXPECT_EQ("fluttered to the open", analyzer_->get_request_result(38).first);
    EXPECT_GE(50, analyzer_->get_request_result(38).second);

    EXPECT_EQ("fluttered amidst the open", analyzer_->get_request_result(39).first);
    EXPECT_GE(50, analyzer_->get_request_result(39).second);

    EXPECT_EQ("fluttered round the open", analyzer_->get_request_result(40).first);
    EXPECT_GE(50, analyzer_->get_request_result(40).second);

    EXPECT_EQ("fluttered beyond the open", analyzer_->get_request_result(41).first);
    EXPECT_GE(50, analyzer_->get_request_result(41).second);

    EXPECT_EQ("fluttered like the open", analyzer_->get_request_result(42).first);
    EXPECT_GE(50, analyzer_->get_request_result(42).second);

    EXPECT_EQ("fluttered minus the open", analyzer_->get_request_result(43).first);
    EXPECT_GE(50, analyzer_->get_request_result(43).second);

    EXPECT_EQ("fluttered nearest the open", analyzer_->get_request_result(44).first);
    EXPECT_GE(50, analyzer_->get_request_result(44).second);

    EXPECT_EQ("fluttered outside the open", analyzer_->get_request_result(45).first);
    EXPECT_GE(100, analyzer_->get_request_result(45).second);

    EXPECT_EQ("fluttered since the open", analyzer_->get_request_result(46).first);
    EXPECT_GE(50, analyzer_->get_request_result(46).second);

    EXPECT_EQ("fluttered throughout the open", analyzer_->get_request_result(47).first);
    EXPECT_GE(50, analyzer_->get_request_result(47).second);

    EXPECT_EQ("fluttered versus the open", analyzer_->get_request_result(48).first);
    EXPECT_GE(50, analyzer_->get_request_result(48).second);
}
