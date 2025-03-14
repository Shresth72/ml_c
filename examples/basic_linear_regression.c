#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {{0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8}};
#define train_count (sizeof(train) / sizeof(train[0]))

float rand_float(void) { return (float)rand() / (float)RAND_MAX; }

float cost_function(float w, float b) {
  float result = 0.0f;
  for (size_t i = 0; i < train_count; ++i) {
    float x = train[i][0];
    float y = x * w + b;
    float d = y - train[i][1];
    result += d * d;
  }
  result /= train_count;
  return result;
}

int main() {
  // srand(time(0));
  srand(69);

  float w = rand_float() * 10.0f;
  float b = rand_float() * 2.0f;

  float eps = 1e-3;
  float lrate = 1e-3;

  printf("%f\n", cost_function(w, b));

  for (size_t i = 0; i < 350; ++i) {
    float cost = cost_function(w, b);
    float dweight = (cost_function(w + eps, b) - cost) / eps;
    float dbias = (cost_function(w, b + eps) - cost) / eps;
    w -= lrate * dweight;
    b -= lrate * dbias;
    printf("cost = %f, w = %f, b = %f\n", cost_function(w, b), w, b);
  }

  printf("--------------------\n");
  printf("w = %f, b = %f\n", w, b);

  return 0;
}
