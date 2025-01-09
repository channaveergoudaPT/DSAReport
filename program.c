#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for patient data
typedef struct Patient 
{
    char id[10];
    char name[50];
    char bloodGroup[5];
    float hemoglobin;
    struct Patient* next;
} Patient;

// Array of linked lists for blood groups
Patient* bloodGroups[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
const char* bloodGroupNames[] = {"A+", "B+", "O+", "AB+", "A-", "B-", "O-", "AB-"};

// Function to map blood group to array index
int bloodGroupIndex(const char* bloodGroup) 
{
    for (int i = 0; i < 8; i++) 
    {
        if (strcmp(bloodGroup, bloodGroupNames[i]) == 0) {
            return i;
        }
    }
    return -1; // Invalid blood group
}

// Function to add a patient to the linked list
void addPatient(const char* id, const char* name, const char* bloodGroup, float hemoglobin) 
{
    int index = bloodGroupIndex(bloodGroup);
    if (index == -1) 
    {
        printf("Invalid blood group: %s\n", bloodGroup);
        return;
    }

    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    strcpy(newPatient->id, id);
    strcpy(newPatient->name, name);
    strcpy(newPatient->bloodGroup, bloodGroup);
    newPatient->hemoglobin = hemoglobin;
    newPatient->next = bloodGroups[index];
    bloodGroups[index] = newPatient;
}

// Function to sort a linked list by hemoglobin level in descending order
Patient* sortPatientsByHemoglobin(Patient* head)
{
    if (!head || !head->next) return head;

    Patient* sorted = NULL;
    Patient* current = head;

    while (current)
    {
        Patient* next = current->next;

        if (!sorted || current->hemoglobin > sorted->hemoglobin) {
            current->next = sorted;
            sorted = current;
        } else {
            Patient* temp = sorted;
            while (temp->next && temp->next->hemoglobin >= current->hemoglobin) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    return sorted;
}

// Function to display patients of a specific blood group in descending order of hemoglobin
void displayPatientsByBloodGroup(const char* bloodGroup) 

{
    int index = bloodGroupIndex(bloodGroup);
    if (index == -1)
    {
        printf("Invalid blood group: %s\n", bloodGroup);
        return;
    }

    // Sort the linked list for the given blood group
    bloodGroups[index] = sortPatientsByHemoglobin(bloodGroups[index]);

    Patient* current = bloodGroups[index];
    if (!current)
    {
        printf("No patients found for blood group %s.\n", bloodGroup);
        return;
    }

    printf("\nPatients with Blood Group %s (Sorted by Hemoglobin in Descending Order):\n", bloodGroup);
    while (current)
    {
        printf("  %s [ID: %s, Hemoglobin: %.2f g/dL]\n", current->name, current->id, current->hemoglobin);
        current = current->next;
    }
}

int main() 
{
    // Embedded dataset
    const char* dataset[] = 
    {
        "P001,John Doe,A+,13.4", "P002,Jane Smith,B+,11.2", "P003,Alice Johnson,O-,15.1",
        "P004,Robert Brown,AB+,12.8", "P005,Emily Davis,A+,14.3", "P006,Michael Miller,B-,10.7",
        "P007,Sarah Wilson,O+,12.6", "P008,David Moore,AB-,13.9", "P009,Laura Taylor,A-,14.5",
        "P010,James Anderson,B+,12.3", "P011,Linda Thomas,O-,13.7", "P012,Daniel Jackson,AB+,11.9",
        "P013,Nancy White,A+,12.1", "P014,Karen Harris,O+,14.8", "P015,Kevin Martin,B-,13.3",
        "P016,Megan Garcia,AB-,10.5", "P017,Paul Martinez,A-,15.2", "P018,Angela Robinson,O+,12.9",
        "P019,Steve Clark,B+,13.6", "P020,Sandra Lewis,AB+,12.4", "P021,Rachel Walker,A+,13.1",
        "P022,Samuel Hall,O-,14.0", "P023,Carol Young,B-,12.8", "P024,Brian King,AB-,11.7",
        "P025,Lisa Wright,O+,13.9", "P026,Eric Lopez,A-,14.4", "P027,Anna Hill,B+,13.0",
        "P028,Jerry Scott,AB+,10.8", "P029,Martha Green,A+,14.0", "P030,Justin Adams,O-,15.0",
        "P031,Betty Baker,B-,11.4", "P032,Frank Nelson,AB-,14.1", "P033,Susan Carter,A-,12.6",
        "P034,Henry Mitchell,O+,14.2", "P035,Patricia Perez,B+,11.6", "P036,Carl Roberts,AB+,13.8",
        "P037,Dorothy Turner,A+,14.9", "P038,Jack Phillips,O-,12.5", "P039,Jennifer Campbell,B-,12.3",
        "P040,Edward Parker,AB-,13.5", "P041,Michelle Evans,O+,13.7", "P042,Barbara Edwards,A-,15.3",
        "P043,Ronald Collins,B+,10.9", "P044,Helen Stewart,AB+,13.2", "P045,Charles Morris,A+,14.4",
        "P046,Stephanie Reed,O-,14.6", "P047,George Kelly,B-,13.0", "P048,Brenda Cooper,AB-,12.0",
        "P049,Arthur Rivera,O+,15.0", "P050,Diane Cox,A-,13.9"
    };
    int numRecords = sizeof(dataset) / sizeof(dataset[0]);

    // Parse and process the dataset
    for (int i = 0; i < numRecords; i++) 
    {
        char id[10], name[50], bloodGroup[5];
        float hemoglobin;

        if (sscanf(dataset[i], "%[^,],%[^,],%[^,],%f", id, name, bloodGroup, &hemoglobin) == 4) {
            addPatient(id, name, bloodGroup, hemoglobin);
        } 
        else 
        {
            printf("Invalid record: %c\n", dataset[i]);
        }
    }

    // Ask the user for a blood group and display the results
    char inputBloodGroup[5];
    printf("Enter a blood group (e.g., A+, B+, O+, AB-, etc.): ");
    scanf("%s", inputBloodGroup);

    displayPatientsByBloodGroup(inputBloodGroup);

    return 0;
}
