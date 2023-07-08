// RUN: %clang_cc1 -fsyntax-only -verify %s

struct FOOO_A_B { // expected-note{{'FOOO_A_B' declared here}} expected-note{{definition of 'FOOO_A_B' is not complete until the closing '}'}}
  FOOO_A v0; // expected-error{{unknown type name 'FOOO_A'; did you mean 'FOOO_A_B'}} expected-error{{field has incomplete type 'FOOO_A_B}}
};

RWStructuredBuffer<FOOO_A_B> Input;

void main() {}
