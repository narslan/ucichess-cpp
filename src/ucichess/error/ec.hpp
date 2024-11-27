#pragma once

static struct ec_node {
  struct ec_node* ec_next;
  int ec_errno;
  char* ec_context;
} *ec_head, ec_node_emergency;
static char ec_s_emergency[100];

static void ec_push(const char* fcn, const char* file, int line, const char* str, int errno_arg) {
  auto node = ec_node();
  node.ec_errno = errno_arg;

  //fmt::print("{} {} {} {} {} {} {} {}", errno_arg, fcn, "{", file, ":", line, "}", str);
}

;
// namespace ucichess
