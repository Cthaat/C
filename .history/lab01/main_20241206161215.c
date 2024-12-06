#include "Expression.c"
#include "Ploy.c"
#include "dancer.c"

void PloyQuestion () {
    Node *poly1 = NULL;
    Node *poly2 = NULL;
    addNode(&poly1, create(1, 2));
    addNode(&poly1, create(2, 1));
    addNode(&poly1, create(3, 0));
    addNode(&poly2, create(2, 2));
    addNode(&poly2, create(3, 1));
    addNode(&poly2, create(4, 0));
    Node *result = addPloy(poly1, poly2);
    print(result);
}

void ExpressionQuestion () {
    
}

void DancerQuestion (){
    Dancer A[] = {{"A", 'M'}, {"B", 'M'}, {"C", 'M'}, {"D", 'M'}, {"E", 'M'}, {"F", 'M'}, {"G", 'M'}, {"H", 'M'}, {"I", 'M'}, {"J", 'M'}, {"K", 'F'}, {"L", 'F'}, {"M", 'F'}, {"N", 'F'}, {"O", 'F'}, {"P", 'F'}, {"Q", 'F'}, {"R", 'F'}, {"S", 'F'}, {"T", 'F'}, {"U", 'F'}, {"V", 'F'}, {"W", 'F'}, {"X", 'F'}, {"Y", 'F'}, {"Z", 'F'}};
    DancerQueue AQueue;
    AQueue.base = A;
    AQueue.front = sizeof (A) / sizeof (Dancer);
    AQueue.rare = 0;
    DancerQueueSort (&AQueue);
    DancerPartner (&MaleQueue, &FemaleQueue);
}

int main () {
    printf ("Welcome to lab01\n");
    int question = 1;
    a:
    printf ("Choose a question:\n1. Ploy\n2. Expression\n3. Dancer\n0. Exit\n");
    scanf ("%d", &question);
    switch (question) {
        case 0:
            printf ("Exiting...\n");
            return 0;
        case 1:
            PloyQuestion();
            break;
        case 2:
            ExpressionQuestion();
            break;
        case 3:
            DancerQuestion();
            break;
        default:
            printf ("Invalid question number\n");
            break;
    }
    goto a;
}