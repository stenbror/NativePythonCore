//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#ifndef SYMBOL_H
#define SYMBOL_H

enum class SymbolType {
    kw_eof,
    kw_newline,
    kw_indent,
    kw_dedent
};

class Symbol {
    SymbolType m_symbol = SymbolType::kw_eof;
};

class LiteralSymbol : public Symbol {

};

#endif //SYMBOL_H
