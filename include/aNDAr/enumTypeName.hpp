// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.

// Interface for multi-dimensional array struct
#ifndef INCLUDEGUARD_ENUMTYPENAME
#define INCLUDEGUARD_ENUMTYPENAME
struct curlyBracketpair{
    enum {opening, closing} variant;
    static int total=0; // goes one up for each {
    int counterID;
};

struct enumEntry {
    enum typeOf {enumName, value, synonyme};
    static std::vector<typeOf> pureEnum;
    static const int makeNew(std::string_view text) // -1 = new
    {
        const int lastIndex{pureEnum.size()};
        pureEnum.emplace_back(text,-1);
        return lastIndex;
    }
    enumEntry(std::string_view text, const int forIndex): belongsToIndex(forIndex) {
        if(sameAsEnumAtIndex > -1)
            if(sameAsEnumAtIndex <= pureEnum.size()) pureEnum.emplace_back(text, sameAsEnumAtIndex+1);
            else
    }
    const int belongsToIndex;
    std::string_view enumName;
    std::vector<std::string_view> synonyme;
};

// wird zu Programmstart angelegt.
// Geht durch alle Datein der Verzeichnisse und trägt enum namen ein.
    // namespace {}
    // enum (class) ENUM_NAME
    // ab hier Werte zwischen { und }
// Geht erneut durch jede Datei und speichert synonyme dafür ab:
        // ZEILE mit ENUM_NAME
            // typedef ENUM_NAME, SYNONYME
            // using SYNONYM = ENUM_NAME (or diffrent synonym).
struct enumTypeName {
    std::vector<std::string_view> names;
    static void register(const int line, std::string_view file) {
        std::cout << "Register enum name at line: " << line << " in file »" << file << "«." << std::endl;
    }

};

#endif // INCLUDEGUARD_ENUMTYPENAME
