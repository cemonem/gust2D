#include <gust/tform2.h>
#include <gtest/gtest.h>

using namespace gust;

TEST(Tform2, vector_tform_multiplication_test0) {
    Tform2 t1{{89.65703166453943, 48.26676306562209}, {-0.9306965207170657, 0.36579227209599235}, false};
    EXPECT_NEAR(t1.getDirection().x, -0.9306965207170657, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.36579227209599235, 1e-05);
    EXPECT_NEAR(t1.translation.x, 89.65703166453943, 1e-05);
    EXPECT_NEAR(t1.translation.y, 48.26676306562209, 1e-05);
    Vec2 v1{15.252238029961429, 14.739393847257121};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 70.07027043219995, 1e-05);
    EXPECT_NEAR(v2.y, 40.128011298029854, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test1) {
    Tform2 t1{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    EXPECT_NEAR(t1.getDirection().x, 0.9999946982177618, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, -0.003256307167251994, 1e-05);
    EXPECT_NEAR(t1.translation.x, 32.43393101909735, 1e-05);
    EXPECT_NEAR(t1.translation.y, 20.342569757015593, 1e-05);
    Vec2 v1{36.4741064989217, 67.1757365255037};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 69.12658897256249, 1e-05);
    EXPECT_NEAR(v2.y, 87.39917923698098, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test2) {
    Tform2 t1{{16.555997880792507, 20.49997478327832}, {0.5735028822625723, -0.8192035424951006}, false};
    EXPECT_NEAR(t1.getDirection().x, 0.5735028822625723, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, -0.8192035424951006, 1e-05);
    EXPECT_NEAR(t1.translation.x, 16.555997880792507, 1e-05);
    EXPECT_NEAR(t1.translation.y, 20.49997478327832, 1e-05);
    Vec2 v1{27.00397103996591, 63.137412754690814};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 83.76524529736605, 1e-05);
    EXPECT_NEAR(v2.y, 34.58771423932001, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test3) {
    Tform2 t1{{83.91062385780216, 90.92916415414288}, {-0.6002216928705997, -0.7998336823412424}, false};
    EXPECT_NEAR(t1.getDirection().x, -0.6002216928705997, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, -0.7998336823412424, 1e-05);
    EXPECT_NEAR(t1.translation.x, 83.91062385780216, 1e-05);
    EXPECT_NEAR(t1.translation.y, 90.92916415414288, 1e-05);
    Vec2 v1{40.04597045407567, 82.09414485774256};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 125.53582585943445, 1e-05);
    EXPECT_NEAR(v2.y, 9.624361541652462, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test4) {
    Tform2 t1{{89.65703166453943, 48.26676306562209}, {-0.9306965207170657, 0.36579227209599235}, false};
    EXPECT_NEAR(t1.getDirection().x, -0.9306965207170657, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.36579227209599235, 1e-05);
    EXPECT_NEAR(t1.translation.x, 89.65703166453943, 1e-05);
    EXPECT_NEAR(t1.translation.y, 48.26676306562209, 1e-05);
    Vec2 v1{40.04597045407567, 82.09414485774256};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 22.35698252090161, 1e-05);
    EXPECT_NEAR(v2.y, -13.489465404036395, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test5) {
    Tform2 t1{{16.555997880792507, 20.49997478327832}, {0.5735028822625723, -0.8192035424951006}, false};
    EXPECT_NEAR(t1.getDirection().x, 0.5735028822625723, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, -0.8192035424951006, 1e-05);
    EXPECT_NEAR(t1.translation.x, 16.555997880792507, 1e-05);
    EXPECT_NEAR(t1.translation.y, 20.49997478327832, 1e-05);
    Vec2 v1{27.00397103996591, 63.137412754690814};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 83.76524529736605, 1e-05);
    EXPECT_NEAR(v2.y, 34.58771423932001, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test6) {
    Tform2 t1{{95.38727732229593, 33.86969022764836}, {0.12296430493875556, 0.9924110941091543}, false};
    EXPECT_NEAR(t1.getDirection().x, 0.12296430493875556, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.9924110941091543, 1e-05);
    EXPECT_NEAR(t1.translation.x, 95.38727732229593, 1e-05);
    EXPECT_NEAR(t1.translation.y, 33.86969022764836, 1e-05);
    Vec2 v1{65.11643010131132, 32.13108005910401};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 71.5070335734325, 1e-05);
    EXPECT_NEAR(v2.y, 102.44293379537224, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test7) {
    Tform2 t1{{95.38727732229593, 33.86969022764836}, {0.12296430493875556, 0.9924110941091543}, false};
    EXPECT_NEAR(t1.getDirection().x, 0.12296430493875556, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.9924110941091543, 1e-05);
    EXPECT_NEAR(t1.translation.x, 95.38727732229593, 1e-05);
    EXPECT_NEAR(t1.translation.y, 33.86969022764836, 1e-05);
    Vec2 v1{40.04597045407567, 82.09414485774256};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 18.840362126551597, 1e-05);
    EXPECT_NEAR(v2.y, 83.70640504261429, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test8) {
    Tform2 t1{{26.650202265691934, 55.29841109613266}, {-0.39272709864247174, -0.919655058155973}, false};
    EXPECT_NEAR(t1.getDirection().x, -0.39272709864247174, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, -0.919655058155973, 1e-05);
    EXPECT_NEAR(t1.translation.x, 26.650202265691934, 1e-05);
    EXPECT_NEAR(t1.translation.y, 55.29841109613266, 1e-05);
    Vec2 v1{34.590779981385566, 61.08231146724907};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 69.24012230853648, 1e-05);
    EXPECT_NEAR(v2.y, -0.5018536402174618, 1e-05);
}


TEST(Tform2, vector_tform_multiplication_test9) {
    Tform2 t1{{80.42111887957047, 77.98983072068606}, {0.6666849584298306, -0.7453396314455679}, false};
    EXPECT_NEAR(t1.getDirection().x, 0.6666849584298306, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, -0.7453396314455679, 1e-05);
    EXPECT_NEAR(t1.translation.x, 80.42111887957047, 1e-05);
    EXPECT_NEAR(t1.translation.y, 77.98983072068606, 1e-05);
    Vec2 v1{36.4741064989217, 67.1757365255037};
    Vec2 v2 = t1 * v1;
    EXPECT_NEAR(v2.x, 154.8065957585728, 1e-05);
    EXPECT_NEAR(v2.y, 95.58928673847205, 1e-05);
}


TEST(Tform2, tform_multiplication_test0) {
    Tform2 t1{{77.70672602836567, 60.69032191971987}, {-0.976538326376092, -0.21534367211176964}, false};
    Tform2 t2{{77.70672602836567, 60.69032191971987}, {-0.976538326376092, -0.21534367211176964}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 14.892406628297856, 1e-05);
    EXPECT_NEAR(t3.translation.y, -15.30975520572111, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, 0.9072542057628373, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, 0.42058269831941886, 1e-05);
}


TEST(Tform2, tform_multiplication_test1) {
    Tform2 t1{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    Tform2 t2{{80.42111887957047, 77.98983072068606}, {0.6666849584298306, -0.7453396314455679}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 113.1085823681567, 1e-05);
    EXPECT_NEAR(t3.translation.y, 98.0701111267964, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, 0.6642543690274463, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, -0.7475066108255827, 1e-05);
}


TEST(Tform2, tform_multiplication_test2) {
    Tform2 t1{{16.555997880792507, 20.49997478327832}, {0.5735028822625723, -0.8192035424951006}, false};
    Tform2 t2{{32.19668836321892, 5.131358702384514}, {0.24542758641318832, 0.9694149265548767}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 39.22451868321484, 1e-05);
    EXPECT_NEAR(t3.translation.y, -2.9328173747407504, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, 0.9349015701760929, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, 0.35490710627187533, 1e-05);
}


TEST(Tform2, tform_multiplication_test3) {
    Tform2 t1{{95.38727732229593, 33.86969022764836}, {0.12296430493875556, 0.9924110941091543}, false};
    Tform2 t2{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 79.18730119693915, 1e-05);
    EXPECT_NEAR(t3.translation.y, 68.55889314741117, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, 0.12619524836739573, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, 0.9920054230141543, 1e-05);
}


TEST(Tform2, tform_multiplication_test4) {
    Tform2 t1{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    Tform2 t2{{26.650202265691934, 55.29841109613266}, {-0.39272709864247174, -0.919655058155973}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 59.26406060361025, 1e-05);
    EXPECT_NEAR(t3.translation.y, 75.55390642836801, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, -0.3957196958461885, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, -0.9183713422790368, 1e-05);
}


TEST(Tform2, tform_multiplication_test5) {
    Tform2 t1{{89.65703166453943, 48.26676306562209}, {-0.9306965207170657, 0.36579227209599235}, false};
    Tform2 t2{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 39.568757777498725, 1e-05);
    EXPECT_NEAR(t3.translation.y, -32.25699155742734, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, 0.27185065354873306, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, 0.9623394526699645, 1e-05);
}


TEST(Tform2, tform_multiplication_test6) {
    Tform2 t1{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    Tform2 t2{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 111.66801174073736, 1e-05);
    EXPECT_NEAR(t3.translation.y, 85.4211775395906, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, -0.9803956724380216, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, -0.19703889327947327, 1e-05);
}


TEST(Tform2, tform_multiplication_test7) {
    Tform2 t1{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    Tform2 t2{{77.70672602836567, 60.69032191971987}, {-0.976538326376092, -0.21534367211176964}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 110.33787139357318, 1e-05);
    EXPECT_NEAR(t3.translation.y, 80.77953294095482, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, -0.9772343741254581, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, -0.21216262165523897, 1e-05);
}


TEST(Tform2, tform_multiplication_test8) {
    Tform2 t1{{89.65703166453943, 48.26676306562209}, {-0.9306965207170657, 0.36579227209599235}, false};
    Tform2 t2{{26.650202265691934, 55.29841109613266}, {-0.39272709864247174, -0.919655058155973}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 44.626049701301284, 1e-05);
    EXPECT_NEAR(t3.translation.y, 6.549162295854657, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, 0.7019124575653016, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, 0.7122632251595181, 1e-05);
}


TEST(Tform2, tform_multiplication_test9) {
    Tform2 t1{{26.650202265691934, 55.29841109613266}, {-0.39272709864247174, -0.919655058155973}, false};
    Tform2 t2{{32.19668836321892, 5.131358702384514}, {0.24542758641318832, 0.9694149265548767}, false};
    Tform2 t3 = t1 * t2;
    EXPECT_NEAR(t3.translation.x, 18.724770244769726, 1e-05);
    EXPECT_NEAR(t3.translation.y, 23.673340171745558, 1e-05);
    EXPECT_NEAR(t3.getDirection().x, 0.7951412767192175, 1e-05);
    EXPECT_NEAR(t3.getDirection().y, -0.6064242327425023, 1e-05);
}


TEST(Tform2, tform_inverse_test0) {
    Tform2 t1{{95.38727732229593, 33.86969022764836}, {0.12296430493875556, 0.9924110941091543}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, -45.34188659189509, 1e-05);
    EXPECT_NEAR(t2.translation.y, 90.4986293341793, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, 0.12296430493875558, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, -0.9924110941091544, 1e-05);
}


TEST(Tform2, tform_inverse_test1) {
    Tform2 t1{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, 91.10771594219585, 1e-05);
    EXPECT_NEAR(t2.translation.y, -26.31148675716422, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, 0.0990058775072937, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, 0.9950868485810725, 1e-05);
}


TEST(Tform2, tform_inverse_test2) {
    Tform2 t1{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, -32.367517405757866, 1e-05);
    EXPECT_NEAR(t2.translation.y, -20.44807674718022, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, 0.9999946982177618, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, 0.003256307167251994, 1e-05);
}


TEST(Tform2, tform_inverse_test3) {
    Tform2 t1{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, 91.10771594219585, 1e-05);
    EXPECT_NEAR(t2.translation.y, -26.31148675716422, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, 0.0990058775072937, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, 0.9950868485810725, 1e-05);
}


TEST(Tform2, tform_inverse_test4) {
    Tform2 t1{{26.650202265691934, 55.29841109613266}, {-0.39272709864247174, -0.919655058155973}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, 61.321720086587014, 1e-05);
    EXPECT_NEAR(t2.translation.y, -2.791808765200516, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, -0.3927270986424717, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, 0.919655058155973, 1e-05);
}


TEST(Tform2, tform_inverse_test5) {
    Tform2 t1{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, 91.10771594219585, 1e-05);
    EXPECT_NEAR(t2.translation.y, -26.31148675716422, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, 0.0990058775072937, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, 0.9950868485810725, 1e-05);
}


TEST(Tform2, tform_inverse_test6) {
    Tform2 t1{{16.555997880792507, 20.49997478327832}, {0.5735028822625723, -0.8192035424951006}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, 7.298739460154288, 1e-05);
    EXPECT_NEAR(t2.translation.y, -25.31952673800677, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, 0.5735028822625723, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, 0.8192035424951006, 1e-05);
}


TEST(Tform2, tform_inverse_test7) {
    Tform2 t1{{32.19668836321892, 5.131358702384514}, {0.24542758641318832, 0.9694149265548767}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, -12.876371235081217, 1e-05);
    EXPECT_NEAR(t2.translation.y, 29.95257330359358, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, 0.24542758641318832, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, -0.9694149265548767, 1e-05);
}


TEST(Tform2, tform_inverse_test8) {
    Tform2 t1{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, -32.367517405757866, 1e-05);
    EXPECT_NEAR(t2.translation.y, -20.44807674718022, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, 0.9999946982177618, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, 0.003256307167251994, 1e-05);
}


TEST(Tform2, tform_inverse_test9) {
    Tform2 t1{{26.650202265691934, 55.29841109613266}, {-0.39272709864247174, -0.919655058155973}, false};
    Tform2 t2 = t1.inverse();
    EXPECT_NEAR(t2.translation.x, 61.321720086587014, 1e-05);
    EXPECT_NEAR(t2.translation.y, -2.791808765200516, 1e-05);
    EXPECT_NEAR(t2.getDirection().x, -0.3927270986424717, 1e-05);
    EXPECT_NEAR(t2.getDirection().y, 0.919655058155973, 1e-05);
}


TEST(Tform2, tform_invert_test0) {
    Tform2 t1{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, 91.10771594219585, 1e-05);
    EXPECT_NEAR(t1.translation.y, -26.31148675716422, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, 0.0990058775072937, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.9950868485810725, 1e-05);
}


TEST(Tform2, tform_invert_test1) {
    Tform2 t1{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, -32.367517405757866, 1e-05);
    EXPECT_NEAR(t1.translation.y, -20.44807674718022, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, 0.9999946982177618, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.003256307167251994, 1e-05);
}


TEST(Tform2, tform_invert_test2) {
    Tform2 t1{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, 91.10771594219585, 1e-05);
    EXPECT_NEAR(t1.translation.y, -26.31148675716422, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, 0.0990058775072937, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.9950868485810725, 1e-05);
}


TEST(Tform2, tform_invert_test3) {
    Tform2 t1{{32.43393101909735, 20.342569757015593}, {0.9999946982177618, -0.003256307167251994}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, -32.367517405757866, 1e-05);
    EXPECT_NEAR(t1.translation.y, -20.44807674718022, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, 0.9999946982177618, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.003256307167251994, 1e-05);
}


TEST(Tform2, tform_invert_test4) {
    Tform2 t1{{26.650202265691934, 55.29841109613266}, {-0.39272709864247174, -0.919655058155973}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, 61.321720086587014, 1e-05);
    EXPECT_NEAR(t1.translation.y, -2.791808765200516, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, -0.3927270986424717, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.919655058155973, 1e-05);
}


TEST(Tform2, tform_invert_test5) {
    Tform2 t1{{77.70672602836567, 60.69032191971987}, {-0.976538326376092, -0.21534367211176964}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, 88.95287296774362, 1e-05);
    EXPECT_NEAR(t1.translation.y, 42.532773663978006, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, -0.9765383263760918, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.2153436721117696, 1e-05);
}


TEST(Tform2, tform_invert_test6) {
    Tform2 t1{{83.91062385780216, 90.92916415414288}, {-0.6002216928705997, -0.7998336823412424}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, 123.09318489937755, 1e-05);
    EXPECT_NEAR(t1.translation.y, -12.53688642782853, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, -0.6002216928705997, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.7998336823412425, 1e-05);
}


TEST(Tform2, tform_invert_test7) {
    Tform2 t1{{32.19668836321892, 5.131358702384514}, {0.24542758641318832, 0.9694149265548767}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, -12.876371235081217, 1e-05);
    EXPECT_NEAR(t1.translation.y, 29.95257330359358, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, 0.24542758641318832, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, -0.9694149265548767, 1e-05);
}


TEST(Tform2, tform_invert_test8) {
    Tform2 t1{{17.162015074126824, 93.26508177325383}, {0.09900587750729373, -0.9950868485810728}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, 91.10771594219585, 1e-05);
    EXPECT_NEAR(t1.translation.y, -26.31148675716422, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, 0.0990058775072937, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.9950868485810725, 1e-05);
}


TEST(Tform2, tform_invert_test9) {
    Tform2 t1{{26.650202265691934, 55.29841109613266}, {-0.39272709864247174, -0.919655058155973}, false};
    t1.invert();
    EXPECT_NEAR(t1.translation.x, 61.321720086587014, 1e-05);
    EXPECT_NEAR(t1.translation.y, -2.791808765200516, 1e-05);
    EXPECT_NEAR(t1.getDirection().x, -0.3927270986424717, 1e-05);
    EXPECT_NEAR(t1.getDirection().y, 0.919655058155973, 1e-05);
}


