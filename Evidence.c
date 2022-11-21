#include <defs.h>

void initEvidence(float value, EvidenceEnumType reading, EvidenceType* ev) {
    ev->type = reading;
    ev->value = value;
};

