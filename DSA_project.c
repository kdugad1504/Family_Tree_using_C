#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person {
    char name[30];
    char gender;
    int age;
    struct person *elder, *younger;
} person;

person *create();
person *insert(person *, char n[30], char, int);
person *find(person *, char, char, char);
void inorder(person *);
int countFemales(person *);
int countMales(person *);
void displayMenu();

void main() {
    person *root = NULL;
    int op;
    do {
        displayMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                root = create();
                break;
            case 2:
                printf("\nFamily Tree: \n");
                inorder(root);
                break;
            case 3:
                printf("\nNumber of males in the family: %d\n", countMales(root));
                break;
            case 4:
                printf("\nNumber of females in the family: %d\n", countFemales(root));
                break;
            case 5:
                printf("\nExiting the program...\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a valid option.\n");
        }
    } while (op != 5);
}

void displayMenu() {
    printf("\n\n=== Family Tree Management ===\n");
    printf("\n\t1: Add a member to the family");
    printf("\n\t2: Display the family tree");
    printf("\n\t3: Male count of the family");
    printf("\n\t4: Female count of the family");
    printf("\n\t5: Exit\n");
}

person *insert(person *T, char n[30], char g, int a) {
    person *p, *q, *r;
    r = (person *)malloc(sizeof(person));
    strcpy(r->name, n);
    r->age = a;
    r->gender = g;
    r->younger = NULL;
    r->elder = NULL;

    if (T == NULL)
        return r;
    p = T;
    while (p != NULL) {
        q = p;
        if (a > p->age)
            p = p->elder;
        else if (a < p->age)
            p = p->younger;#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person {
    char name[30];
    char gender;
    int age;
    struct person *elder, *younger;
} person;

person *create();
person *insert(person *, char n[30], char, int);
person *find(person *, char n[30]);
person *deleteMember(person *, char n[30]);
void inorder(person *);
int countFemales(person *);
int countMales(person *);
void countAgeGroups(person *, int *, int *, int *);
void displayMenu();

void main() {
    person *root = NULL;
    int op;
    char name[30];
    do {
        displayMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                root = create();
                break;
            case 2:
                printf("\nFamily Tree: \n");
                inorder(root);
                break;
            case 3:
                printf("\nNumber of males in the family: %d\n", countMales(root));
                break;
            case 4:
                printf("\nNumber of females in the family: %d\n", countFemales(root));
                break;
            case 5:
                printf("\nEnter the name of the family member to find: ");
                scanf("%s", name);
                person *found = find(root, name);
                if (found) {
                    printf("Member found: %s, %c, %d\n", found->name, found->gender, found->age);
                } else {
                    printf("Member not found.\n");
                }
                break;
            case 6:
                printf("\nEnter the name of the family member to delete: ");
                scanf("%s", name);
                root = deleteMember(root, name);
                printf("Member deleted (if existed).\n");
                break;
            case 7:
                {
                    int children = 0, adults = 0, elderly = 0;
                    countAgeGroups(root, &children, &adults, &elderly);
                    printf("\nAge Group Counts:\n");
                    printf("Children (0-17): %d\n", children);
                    printf("Adults (18-49): %d\n", adults);
                    printf("Elderly (50+): %d\n", elderly);
                }
                break;
            case 8:
                printf("\nExiting the program...\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a valid option.\n");
        }
    } while (op != 8);
}

void displayMenu() {
    printf("\n\n=== Family Tree Management ===\n");
    printf("\n\t1: Add a member to the family");
    printf("\n\t2: Display the family tree");
    printf("\n\t3: Male count of the family");
    printf("\n\t4: Female count of the family");
    printf("\n\t5: Find a family member");
    printf("\n\t6: Delete a family member");
    printf("\n\t7: Display age group counts");
    printf("\n\t8: Exit\n");
}

person *insert(person *T, char n[30], char g, int a) {
    person *p, *q, *r;
    r = (person *)malloc(sizeof(person));
    strcpy(r->name, n);
    r->age = a;
    r->gender = g;
    r->younger = NULL;
    r->elder = NULL;

    if (T == NULL)
        return r;
    p = T;
    while (p != NULL) {
        q = p;
        if (a > p->age)
            p = p->elder;
        else if (a < p->age)
            p = p->younger;
    }
    if (a > q->age)
        q->elder = r;
    else if (a < q->age)
        q->younger = r;

    return T;
}

person *create() {
    int j, x, i;
    char n[30], g;
    person *root;
    root = NULL;
    printf("\nEnter number of core family members: ");
    scanf("%d", &j);
    for (i = 0; i < j; i++) {
        printf("\nEnter %d Member name: ", (i + 1));
        scanf("%s", n);
        printf("\nEnter %d Member gender (m/f): ", (i + 1));
        scanf(" %c", &g);
        printf("\nEnter %d Member age: ", (i + 1));
        scanf("%d", &x);
        root = insert(root, n, g, x);
    }
    return root;
}

void inorder(person *T) {
    if (T != NULL) {
        inorder(T->younger);
        printf("%s\t%d\n", T->name, T->age);
        inorder(T->elder);
    }
}

int countMales(person *T) {
    if (T == NULL)
        return 0;
    int count = 0;
    if (T->gender == 'm')
        count++;
    count += countMales(T->elder);
    count += countMales(T->younger);
    return count;
}

int countFemales(person *T) {
    if (T == NULL)
        return 0;
    int count = 0;
    if (T->gender == 'f')
        count++;
    count += countFemales(T->elder);
    count += countFemales(T->younger);
    return count;
}

person *find(person *T, char n[30]) {
    if (T == NULL)
        return NULL;
    if (strcmp(T->name, n) == 0)
        return T;
    person *found = find(T->younger, n);
    if (found == NULL)
        found = find(T->elder, n);
    return found;
}

person *deleteMember(person *root, char n[30]) {
    if (root == NULL)
        return NULL;

    if (strcmp(root->name, n) == 0) {
        if (root->younger == NULL && root->elder == NULL) {
            free(root);
            return NULL;
        } else if (root->younger == NULL) {
            person *temp = root->elder;
            free(root);
            return temp;
        } else if (root->elder == NULL) {
            person *temp = root->younger;
            free(root);
            return temp;
        } else {
            person *temp = root->younger;
            while (temp->elder != NULL)
                temp = temp->elder;
            strcpy(root->name, temp->name);
            root->age = temp->age;
            root->gender = temp->gender;
            root->younger = deleteMember(root->younger, temp->name);
        }
    } else if (strcmp(root->name, n) > 0) {
        root->younger = deleteMember(root->younger, n);
    } else {
        root->elder = deleteMember(root->elder, n);
    }
    return root;
}

void countAgeGroups(person *T, int *children, int *adults, int *elderly) {
    if (T == NULL)
        return;
    if (T->age >= 0 && T->age <= 17)
        (*children)++;
    else if (T->age >= 18 && T->age <= 49)
        (*adults)++;
    else if (T->age >= 50)
        (*elderly)++;
    countAgeGroups(T->younger, children, adults, elderly);
    countAgeGroups(T->elder, children, adults, elderly);
}

    }
    if (a > q->age)
        q->elder = r;
    else if (a < q->age)
        q->younger = r;

    return T;
}

person *create() {
    int j, x, i;
    char n[30], g;
    person *root;
    root = NULL;
    printf("\nEnter number of core family members: ");
    scanf("%d", &j);
    for (i = 0; i < j; i++) {
        printf("\nEnter %d Member name: ", (i + 1));
        scanf("%s", n);
        printf("\nEnter %d Member gender (m/f): ", (i + 1));
        scanf(" %c", &g);
        printf("\nEnter %d Member age: ", (i + 1));
        scanf("%d", &x);
        root = insert(root, n, g, x);
    }
    return root;
}

void inorder(person *T) {
    if (T != NULL) {
        inorder(T->younger);
        printf("%s\t", T->name);
        printf("%d\t", T->age);
        inorder(T->elder);
    }
}

int countMales(person *T) {
    if (T == NULL)
        return 0;
    int count = 0;
    if (T->gender == 'm')
        count++;
    count += countMales(T->elder);
    count += countMales(T->younger);
    return count;
}

int countFemales(person *T) {
    if (T == NULL)
        return 0;
    int count = 0;
    if (T->gender == 'f')
        count++;
    count += countFemales(T->elder);
    count += countFemales(T->younger);
    return count;
}
