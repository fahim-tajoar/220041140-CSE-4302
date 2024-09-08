#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxline 300

struct Spell {
    int id;
    char inc[100];
    char name[100];
    char eff[100];
    char lig[100];
};

void readdb(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    char line[maxline];
    printf("Spell ID | Incantation | Spell Name | Effect | Light\n");
    printf("____________________________________________________\n");
    while (fgets(line, maxline, fp)) {
        struct Spell spell;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^\n]", &spell.id, spell.inc, spell.name, spell.eff, spell.lig);
        printf("%d | %s | %s | %s | %s\n", spell.id, spell.inc, spell.name, spell.eff, spell.lig);
    }

    fclose(fp);
}

void insertdb(const char *filename) {
    FILE *fp = fopen(filename, "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    struct Spell newsp;
    printf("Enter spell ID: ");
    scanf("%d", &newsp.id);
    getchar(); // consume newline after scanf

    printf("Enter incantation: ");
    fgets(newsp.inc, sizeof(newsp.inc), stdin);
    strtok(newsp.inc, "\n"); // remove trailing newline

    printf("Enter spell name: ");
    fgets(newsp.name, sizeof(newsp.name), stdin);
    strtok(newsp.name, "\n");

    printf("Enter spell effect: ");
    fgets(newsp.eff, sizeof(newsp.eff), stdin);
    strtok(newsp.eff, "\n");

    printf("Enter light: ");
    fgets(newsp.lig, sizeof(newsp.lig), stdin);
    strtok(newsp.lig, "\n");

    fprintf(fp, "%d,%s,%s,%s,%s\n", newsp.id, newsp.inc, newsp.name, newsp.eff, newsp.lig);
    fclose(fp);
}

void updatedb(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    struct Spell spells[100];
    int c = 0;
    char line[maxline];

    while (fgets(line, maxline, fp)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^\n]", &spells[c].id, spells[c].inc, spells[c].name, spells[c].eff, spells[c].lig);
        c++;
    }
    fclose(fp);

    int id;
    printf("Enter the ID of the spell to update: ");
    scanf("%d", &id);
    getchar(); // consume newline

    for (int i = 0; i < c; i++) {
        if (spells[i].id == id) {
            printf("Enter new incantation: ");
            fgets(spells[i].inc, sizeof(spells[i].inc), stdin);
            strtok(spells[i].inc, "\n");

            printf("Enter new spell name: ");
            fgets(spells[i].name, sizeof(spells[i].name), stdin);
            strtok(spells[i].name, "\n");

            printf("Enter new spell effect: ");
            fgets(spells[i].eff, sizeof(spells[i].eff), stdin);
            strtok(spells[i].eff, "\n");

            printf("Enter new light: ");
            fgets(spells[i].lig, sizeof(spells[i].lig), stdin);
            strtok(spells[i].lig, "\n");
            break;
        }
    }

    fp = fopen(filename, "w");
    for (int i = 0; i < c; i++) {
        fprintf(fp, "%d,%s,%s,%s,%s\n", spells[i].id, spells[i].inc, spells[i].name, spells[i].eff, spells[i].lig);
    }
    fclose(fp);
}

void searchdb(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    char line[maxline];
    struct Spell spell;
    int found = 0;

    while (fgets(line, maxline, fp)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^\n]", &spell.id, spell.inc, spell.name, spell.eff, spell.lig);
        if (spell.id == id) {
            printf("%d | %s | %s | %s | %s\n", spell.id, spell.inc, spell.name, spell.eff, spell.lig);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Spell with ID %d not found.\n", id);
    }
    fclose(fp);
}

void deletedb(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter the ID to delete: ");
    scanf("%d", &id);

    struct Spell spells[100];
    int c = 0;
    char line[maxline];

    while (fgets(line, maxline, fp)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^\n]", &spells[c].id, spells[c].inc, spells[c].name, spells[c].eff, spells[c].lig);
        c++;
    }
    fclose(fp);

    fp = fopen(filename, "w");
    for (int i = 0; i < c; i++) {
        if (spells[i].id != id) {
            fprintf(fp, "%d,%s,%s,%s,%s\n", spells[i].id, spells[i].inc, spells[i].name, spells[i].eff, spells[i].lig);
        }
    }
    fclose(fp);
}

int main() {
    const char *filename = "spells.txt";
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Read database\n");
        printf("2. Insert new spell\n");
        printf("3. Update a spell\n");
        printf("4. Delete a spell\n");
        printf("5. Search for a spell\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readdb(filename);
                break;
            case 2:
                insertdb(filename);
                break;
            case 3:
                updatedb(filename);
                break;
            case 4:
                deletedb(filename);
                break;
            case 5:
                searchdb(filename);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
