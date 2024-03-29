#include <stdbool.h>

// parse
typedef enum {
  TK_RESERVED,
  TK_IDENT,
  TK_NUM,
  TK_EOF,
} TokenKind;
typedef struct Token Token;

struct Token {
  TokenKind kind;
  Token *next;
  int val;
  char *str;
  int len;
};

typedef enum {
  ND_EQ,
  ND_NEQ,

  ND_GT,
  ND_GTE,
  ND_LT,
  ND_LTE,

  ND_ADD,
  ND_SUB,
  ND_MUL,
  ND_DIV,
  ND_NUM,

  ND_ASSIGN,
  ND_LVAR,
} NodeKind;
typedef struct Node Node;

struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val; // used only when kind == ND_NUM
  int offset; // used only when kind == ND_LVAR
};

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);

bool consume(char *op);
void expect(char *op);
int expect_number();
bool at_eof();

Token *new_token(TokenKind kind, Token *cur, char *str, int len);
Token *tokenize();

Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);
void program();
Node *stmt();
Node *assign();
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

// codegen
void gen(Node *node);

// global variable
char *user_input;
Token *token;
Node *code[100];
