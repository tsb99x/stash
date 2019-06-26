#include "main.h"

#include "panic.h"

// Base challenge

void complement(const char *src_strand, char *dst_buf)
{
    while (*src_strand != '\0') {
        *dst_buf = lookup_base_compl(*src_strand);

        src_strand++;
        dst_buf++;
    }

    *dst_buf = '\0';
}

char lookup_base_compl(const char base)
{
    switch (base) {
    case 'A':
        return 'T';
    case 'T':
        return 'A';
    case 'G':
        return 'C';
    case 'C':
        return 'G';
    case ' ':
        return ' ';
    default:
        panic_m("Failed to complement base of '%c'", base);
    }
}

// Extra part next

struct lookup_item_t {
    const char *const bases;
    const char *const codon;
};

// This is just a tree, think about it!

struct lookup_item_t codon_lookup[] = {

    {"TTT", "Phe"},  {"TTC", "Phe"},

    {"TTA", "Leu"},  {"TTG", "Leu"},  {"CTT", "Leu"}, {"CTC", "Leu"},
    {"CTA", "Leu"},  {"CTG", "Leu"},

    {"ATT", "Ile"},  {"ATC", "Ile"},  {"ATA", "Ile"},

    {"ATG", "Met"},

    {"GTT", "Val"},  {"GTC", "Val"},  {"GTA", "Val"}, {"GTG", "Val"},

    {"TCT", "Ser"},  {"TCC", "Ser"},  {"TCA", "Ser"}, {"TCG", "Ser"},

    {"CCT", "Pro"},  {"CCC", "Pro"},  {"CCA", "Pro"}, {"CCG", "Pro"},

    {"ACT", "Thr"},  {"ACC", "Thr"},  {"ACA", "Thr"}, {"ACG", "Thr"},

    {"GCT", "Ala"},  {"GCC", "Ala"},  {"GCA", "Ala"}, {"GCG", "Ala"},

    {"TAT", "Tyr"},  {"TAC", "Tyr"},

    {"TAA", "STOP"}, {"TAG", "STOP"},

    {"CAT", "His"},  {"CAC", "His"},

    {"CAA", "Gln"},  {"CAG", "Gln"},

    {"AAT", "Asn"},  {"AAC", "Asn"},

    {"AAA", "Lys"},  {"AAG", "Lys"},

    {"GAT", "Asp"},  {"GAC", "Asp"},

    {"GAA", "Glu"},  {"GAG", "Glu"},

    {"TGT", "Cys"},  {"TGC", "Cys"},

    {"TGA", "STOP"},

    {"TGG", "Trp"},

    {"CGT", "Arg"},  {"CGC", "Arg"},  {"CGA", "Arg"}, {"CGG", "Arg"},

    {"AGT", "Ser"},  {"AGC", "Ser"},

    {"AGA", "Arg"},  {"AGG", "Arg"},

    {"GGT", "Gly"},  {"GGC", "Gly"},  {"GGA", "Gly"}, {"GGG", "Gly"},

};

// Much better way would be to process simple list, that is.

#define count_m(X) sizeof X / sizeof X[0]

void convert_to_codon(const char *const bases, char **dst_buf)
{
    for (size_t i = 0; i < count_m(codon_lookup); i++) {
        if (!strncmp(bases, codon_lookup[i].bases, 3)) {
            size_t codon_len = strlen(codon_lookup[i].codon);

            strncpy(*dst_buf, codon_lookup[i].codon, codon_len);
            *dst_buf += codon_len;

            **dst_buf = ' ';
            *dst_buf += 1;

            return;
        }
    }

    panic_m("Failed to find codon for bases of '%s'", bases);
}

void identify(const char *src_strand, char *dst_buf)
{
    char bases_buf[] = "###";
    int bases_index = 0;

    while (*src_strand != '\0') {
        if (*src_strand != ' ') {
            bases_buf[bases_index] = *src_strand;
            bases_index++;

            if (bases_index == 3) {
                convert_to_codon(bases_buf, &dst_buf);
                bases_index = 0;
            }
        }

        src_strand++;
    }

    if (bases_index != 0) {
        printf("%d of bases at the end of strand does not form codon\n",
               bases_index);
    }

    *dst_buf = '\0';
}
