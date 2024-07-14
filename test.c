#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// temporary bull-shit

// Token types
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    double value;
} Token;

// AST node types
typedef enum {
    AST_NUMBER,
    AST_BIN_OP
} ASTNodeType;

// AST node structure
typedef struct ASTNode {
    ASTNodeType type;
    union {
        double number;
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            TokenType op;
        } bin_op;
    } data;
} ASTNode;

// Function prototypes
Token *tokenize(const char *input);
ASTNode *parse(Token **tokens);
double evaluate(ASTNode *node);
void free_ast(ASTNode *node);
void free_tokens(Token *tokens);

Token *tokenize(const char *input) {
    size_t length = strlen(input);
    Token *tokens = malloc((length + 1) * sizeof(Token));
    size_t pos = 0, token_pos = 0;

    while (pos < length) {
        if (isdigit(input[pos]) || input[pos] == '.') {
            char number[32];
            size_t num_pos = 0;

            while (isdigit(input[pos]) || input[pos] == '.') {
                number[num_pos++] = input[pos++];
            }
            number[num_pos] = '\0';
            tokens[token_pos].type = TOKEN_NUMBER;
            tokens[token_pos].value = atof(number);
            token_pos++;
        } else if (input[pos] == '+') {
            tokens[token_pos++].type = TOKEN_PLUS;
            pos++;
        } else if (input[pos] == '-') {
            tokens[token_pos++].type = TOKEN_MINUS;
            pos++;
        } else if (input[pos] == '*') {
            tokens[token_pos++].type = TOKEN_MULTIPLY;
            pos++;
        } else if (input[pos] == '/') {
            tokens[token_pos++].type = TOKEN_DIVIDE;
            pos++;
        } else if (input[pos] == '(') {
            tokens[token_pos++].type = TOKEN_LPAREN;
            pos++;
        } else if (input[pos] == ')') {
            tokens[token_pos++].type = TOKEN_RPAREN;
            pos++;
        } else {
            pos++;
        }
    }
    tokens[token_pos].type = TOKEN_END;
    return tokens;
}

ASTNode *parse_primary(Token **tokens);
ASTNode *parse_expression(Token **tokens);

ASTNode *parse(Token **tokens) {
    return parse_expression(tokens);
}

ASTNode *parse_expression(Token **tokens) {
    ASTNode *node = parse_primary(tokens);
    Token *token = *tokens;

    while (token->type == TOKEN_PLUS || token->type == TOKEN_MINUS) {
        TokenType op = token->type;
        (*tokens)++;
        ASTNode *right = parse_primary(tokens);

        ASTNode *new_node = malloc(sizeof(ASTNode));
        new_node->type = AST_BIN_OP;
        new_node->data.bin_op.left = node;
        new_node->data.bin_op.right = right;
        new_node->data.bin_op.op = op;

        node = new_node;
        token = *tokens;
    }

    return node;
}

ASTNode *parse_primary(Token **tokens) {
    Token *token = *tokens;

    if (token->type == TOKEN_NUMBER) {
        ASTNode *node = malloc(sizeof(ASTNode));
        node->type = AST_NUMBER;
        node->data.number = token->value;
        (*tokens)++;
        return node;
    } else if (token->type == TOKEN_LPAREN) {
        (*tokens)++;
        ASTNode *node = parse_expression(tokens);
        if ((*tokens)->type != TOKEN_RPAREN) {
            fprintf(stderr, "Expected closing parenthesis\n");
            exit(1);
        }
        (*tokens)++;
        return node;
    } else {
        fprintf(stderr, "Unexpected token: %d\n", token->type);
        exit(1);
    }

    return NULL;
}

double evaluate(ASTNode *node) {
    if (node->type == AST_NUMBER) {
        return node->data.number;
    } else if (node->type == AST_BIN_OP) {
        double left = evaluate(node->data.bin_op.left);
        double right = evaluate(node->data.bin_op.right);

        switch (node->data.bin_op.op) {
            case TOKEN_PLUS: return left + right;
            case TOKEN_MINUS: return left - right;
            case TOKEN_MULTIPLY: return left * right;
            case TOKEN_DIVIDE: return left / right;
            default:
                fprintf(stderr, "Unknown operator: %d\n", node->data.bin_op.op);
                exit(1);
        }
    }

    return 0.0;
}

void free_ast(ASTNode *node) {
    if (node == NULL) return;

    if (node->type == AST_BIN_OP) {
        free_ast(node->data.bin_op.left);
        free_ast(node->data.bin_op.right);
    }

    free(node);
}

void free_tokens(Token *tokens) {
    free(tokens);
}

double evaluate_equation(const char *equation) {
    Token *tokens = tokenize(equation);
    Token *token_ptr = tokens;
    ASTNode *ast = parse(&token_ptr);
    double result = evaluate(ast);
    free_ast(ast);
    free_tokens(tokens);
    return result;
}

int main() {
    const char *equation = "3 + 5 * (2 - 8)";
    double result = evaluate_equation(equation);
    printf("Result: %lf\n", result);
    return 0;
}

