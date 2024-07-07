#ifndef VEC2FLIB
#define VEC2FLIB
struct vec2f {
  float x;
  float y;
};

vec2f add (vec2f a, vec2f b) {
  return (vec2f) {a.x + b.x, a.y + b.y};
}
vec2f sub (vec2f a, vec2f b) {
  return (vec2f) {a.x - b.x, a.y - b.y};
}
vec2f fmul (vec2f a, float m) {
  return (vec2f) {a.x * m, a.y * m};
}
vec2f vmul (vec2f a, vec2f b) {
  return (vec2f) {a.x * b.x, a.y * b.y};
}
float smul (vec2f a, vec2f b) {
  return a.x*b.x + a.y*b.y;
}
vec2f div (vec2f a, int m) {
  return (vec2f) {a.x / m, a.y / m};
}
#endif
