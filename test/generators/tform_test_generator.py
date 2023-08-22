import numpy as np
import random
import os

VECTOR_XY_MAX = 100
PRECISION = 1e-5

def generate_random_tforms(n):
    tforms = []
    for i in range(n):
        theta = np.random.rand() * 2 * np.pi
        c = np.cos(theta)
        s = np.sin(theta)
        x = np.random.rand() * VECTOR_XY_MAX
        y = np.random.rand() * VECTOR_XY_MAX
        tforms.append(np.array([[c, -s, x], [s, c, y], [0, 0, 1]]))
    return tforms

def generate_random_vectors(n):
    vectors = []
    for i in range(n):
        x = np.random.rand() * VECTOR_XY_MAX
        y = np.random.rand() * VECTOR_XY_MAX
        vectors.append(np.array([[x], [y], [1]]))
    return vectors


def get_tform_params(mat):
    c = mat[0, 0]
    s = mat[1, 0]
    x = mat[0, 2]
    y = mat[1, 2]
    return c, s, x, y

def generate_tform_multiplication_test(mat1, mat2, test_name):
    mat3 = np.matmul(mat1, mat2)
    c1, s1, x1, y1 = get_tform_params(mat1)
    c2, s2, x2, y2 = get_tform_params(mat2)
    c3, s3, x3, y3 = get_tform_params(mat3)
    return  f'TEST(Tform2, {test_name}) {{\n' \
            f'    Tform2 t1{{{{{x1}, {y1}}}, {{{c1}, {s1}}}, false}};\n' \
            f'    Tform2 t2{{{{{x2}, {y2}}}, {{{c2}, {s2}}}, false}};\n' \
            f'    Tform2 t3 = t1 * t2;\n' \
            f'    EXPECT_NEAR(t3.translation.x, {x3}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t3.translation.y, {y3}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t3.getDirection().x, {c3}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t3.getDirection().y, {s3}, {PRECISION});\n' \
            f'}}\n'

def generate_vector_tform_multiplication_test(mat, vector, test_name):
    result = np.matmul(mat, vector)
    c1, s1, x1, y1 = get_tform_params(mat)
    x2 = result[0, 0]
    y2 = result[1, 0]
    return  f'TEST(Tform2, {test_name}) {{\n' \
            f'    Tform2 t1{{{{{x1}, {y1}}}, {{{c1}, {s1}}}, false}};\n' \
            f'    EXPECT_NEAR(t1.getDirection().x, {c1}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t1.getDirection().y, {s1}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t1.translation.x, {x1}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t1.translation.y, {y1}, {PRECISION});\n' \
            f'    Vec2 v1{{{vector[0, 0]}, {vector[1, 0]}}};\n' \
            f'    Vec2 v2 = t1 * v1;\n' \
            f'    EXPECT_NEAR(v2.x, {x2}, {PRECISION});\n' \
            f'    EXPECT_NEAR(v2.y, {y2}, {PRECISION});\n' \
            f'}}\n'

def generate_tform_inverse_test(mat, test_name):
    inv = np.linalg.inv(mat)
    c1, s1, x1, y1 = get_tform_params(mat)
    c2, s2, x2, y2 = get_tform_params(inv)
    return  f'TEST(Tform2, {test_name}) {{\n' \
            f'    Tform2 t1{{{{{x1}, {y1}}}, {{{c1}, {s1}}}, false}};\n' \
            f'    Tform2 t2 = t1.inverse();\n' \
            f'    EXPECT_NEAR(t2.translation.x, {x2}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t2.translation.y, {y2}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t2.getDirection().x, {c2}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t2.getDirection().y, {s2}, {PRECISION});\n' \
            f'}}\n'

def generate_tform_invert_test(mat, test_name):
    inv = np.linalg.inv(mat)
    c1, s1, x1, y1 = get_tform_params(mat)
    c2, s2, x2, y2 = get_tform_params(inv)
    return  f'TEST(Tform2, {test_name}) {{\n' \
            f'    Tform2 t1{{{{{x1}, {y1}}}, {{{c1}, {s1}}}, false}};\n' \
            f'    t1.invert();\n' \
            f'    EXPECT_NEAR(t1.translation.x, {x2}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t1.translation.y, {y2}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t1.getDirection().x, {c2}, {PRECISION});\n' \
            f'    EXPECT_NEAR(t1.getDirection().y, {s2}, {PRECISION});\n' \
            f'}}\n'

np.random.seed(336)
random.seed(336)

random_tforms = generate_random_tforms(10)
random_vectors = generate_random_vectors(10)

test_file_str = "#include <gust/tform2.h>\n#include <gtest/gtest.h>\n\n"
test_file_str += "using namespace gust;\n\n"
for i in range(10):
    test_file_str += generate_vector_tform_multiplication_test(random.choice(random_tforms), random.choice(random_vectors), f"vector_tform_multiplication_test{i}")
    test_file_str += "\n\n"

for i in range(10):
    test_file_str += generate_tform_multiplication_test(random.choice(random_tforms), random.choice(random_tforms), f"tform_multiplication_test{i}")
    test_file_str += "\n\n"

for i in range(10):
    test_file_str += generate_tform_inverse_test(random.choice(random_tforms), f"tform_inverse_test{i}")
    test_file_str += "\n\n"

for i in range(10):
    test_file_str += generate_tform_invert_test(random.choice(random_tforms), f"tform_invert_test{i}")
    test_file_str += "\n\n"

print(test_file_str)
with open(os.path.join(os.path.dirname(__file__), "..", "tform2_test.cpp"), "w") as f:
    f.write(test_file_str)
