#ifndef AUDIT_H
#define AUDIT_H

struct audit {
    int audit_id;
    float donation_amount;
    char handled_by[50];
    char compliance_status[10];
};

void add_audit();
void display_audits();
void audit_menu();

#endif /* AUDIT_H */
