#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
typedef int bool;

struct pair {
    int i;
    int n;
};

void swap(int *, int *);
int median(int *, int, int);
struct pair tripartition(int *, int, int);
struct pair partition(int *, int, int);
void quicksort(int *, int, int);

void merge(int *, int, int, int);
void merge_sort(int *, int, int);
void selection_sort(int *, int);
void insertion_sort(int *, int);
void bubble_sort(int *, int);
void add_num(int **, int *, int);
void fill_array(int **, int *);
void print_array(int *, int, int);

int main(){
    int *nums=NULL;
    int size=0;
    struct timespec start, stop;

    fill_array(&nums, &size);

    printf("array filled\n");
    fflush(stdout);

    clock_gettime(CLOCK_MONOTONIC, &start);

    //bubble_sort(nums, size);
    //insertion_sort(nums, size);
    //merge_sort(nums, 0, size-1);
    //selection_sort(nums, size);
    quicksort(nums, 0, size - 1);

    clock_gettime(CLOCK_MONOTONIC, &stop);

    double e_sec = stop.tv_sec - start.tv_sec + (stop.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Seconds: %f\n", e_sec);
    fflush(stdout);

    //print_array(nums, 0, size-1);

    free(nums);

    return 0;
}

/*********************************************************************
 ** Function: swap
 ** Description: Swaps the integer values of two memory locations.
 ** Parameters: int *a - the first memory location.
 **             int *b - the second memory location.
 ** Pre-Conditions: a and b point to valid memory locations (non-null).
 ** Post-Conditions: The values of *a and *b have been swapped.
 ** Return: N/A
 *********************************************************************/
// I found this algorithm on stack overflow, and was intrigued by the
// fact that it swaps two values without using a temporary variable.
// However, I do not believe it is any faster.
void swap(int *a, int *b) {
    if (a != b) { 
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

/*********************************************************************
 ** Function: median
 ** Description: Determines the median value of the leftmost, rightmost,
 **   and central indices of the range, swaps it into the rightmost
 **   index, and returns its value. 
 ** Parameters: int *arr - a pointer to the beginning of the array
 **               being sorted.
 **             int left - the first index of the range.
 **             int right - the last index of the range.
 ** Pre-Conditions: arr is not a null pointer, left and right are
 **   nonnegative integers such that left <= right, and right is a
 **   valid index of arr (right + 1 <= the size of the array).
 ** Post-Conditions: The median value of the left, right, and middle
 **   indices has been swapped into the right index.
 ** Return: The median value.
 *********************************************************************/
// I came up with this method for determining the median of three
// values by constructing and analyzing the truth table of p, q, and r
// values for all six possible arr[left], arr[mid], arr[right] orderings,
// using "don't cares" for impossible combinations of p, q, and r (such
// as p = 1, q = 1, r = 0), a technique learned in ECE 271 Digital Logic
// Design.
int median(int *arr, int left, int right) {
    int mid = (left + right) / 2;
    
    bool p = (arr[left] < arr[mid]);
    bool q = (arr[mid] < arr[right]);
    bool r = (arr[left] < arr[right]);

    if (p != r)
        // left is median, swap it into arr[right].
        swap(&arr[left], &arr[right]);
    else if (p == q)
        // mid is median, swap it into arr[right].
        swap(&arr[mid], &arr[right]);
    // otherwise, right is median, do nothing.

    return arr[right];
}

/*********************************************************************
 ** Function: tripartition
 ** Description: Partitions the elements of the array into three
 **   subarrays containing elements less than, equal to, and greater
 **   than the "pivot" value, respectively.
 ** Parameters: int *arr - a pointer to the beginning of the array
 **               being sorted.
 **             int left - the first index of the range.
 **             int right - the last index of the range.
 ** Pre-Conditions: arr is not a null pointer, left and right are
 **   nonnegative integers such that left <= right, and right is a
 **   valid index of arr (right + 1 <= the size of the array).
 ** Post-Conditions: The values less than the pivot value have been
 **   swapped into the elements from left to result.i - 1, the values
 **   equal to the pivot value have been swapped into result.i to
 **   result.n, and the values greater than the pivot value have been
 **   swapped into result.n + 1 to right.
 ** Return: A struct pair containing the two intermediate boundaries,
 **   result.i and result.n is returned. 
 *********************************************************************/
// This function was constructed from the pseudocode found on the
// "Dutch national flag problem" Wikipedia page.
struct pair tripartition(int *arr, int left, int right) {
    // These two lines offer two different pivot selection methods.
    // Either way the pivot value is stored in arr[right]. Choose one:
    int pivot = median(arr, left, right);
    // int pivot = arr[right];
    int j = left;
    struct pair result = {left, right};

    // The loop invariant is that all elements from index left to
    // result.i - 1 (if any) contain values less than the pivot value,
    // all elements from result.i to j - 1 (if any) contain values
    // equal to the pivot value, and all elements from result.n + 1
    // to right (if any) contain values greater than the pivot value.
    while (j <= result.n) {
        // If the element is less than the pivot value, swap it into
        // the element at index result.i, and increment both result.i
        // and j. If result.i == j, no swap will occur because the
        // element is already in the correct location. If not, the
        // element previously at result.i has a value equal to the pivot
        // value, so j can be incremented while preserving the loop
        // invariant.
        if (arr[j] < pivot)
            swap(&arr[result.i++], &arr[j++]);
        // If the element is greater than the pivot value, swap it into
        // the element at index result.n, and decrement result.n to
        // preserve the loop invariant. However, the value being
        // swapped into arr[j] is unknown, so j cannot be incremented.
        else if (arr[j] > pivot)
            swap(&arr[j], &arr[result.n--]);
        // Otherwise, the element is equal to the pivot value, so
        // j is incremented, preserving the loop invariant.
        else ++j;
    }
    
    return result;
}


/*********************************************************************
 ** Function: partition
 ** Description: Paritions the elements of the array into two subarrays
 **   containing elements less than or equal to and greater than the
 **   "pivot" value, respectively.
 ** Parameters: int *arr - a pointer to the beginning of the array
 **               being sorted.
 **             int left - the first index of the range.
 **             int right - the last index of the range.
 ** Pre-Conditions: arr is not a null pointer, left and right are
 **   nonnegative integers such that left <= right, and right is a
 **   valid index of arr (right + 1 <= the size of the array).
 ** Post-Conditions: The values less than or equal to the pivot value
 **   have been swapped into the elements from left to result.i - 1,
 **   and the values greater than the pivot value have been swapped
 **   into result.i + 1 to right.
 ** Return: A struct pair containing the pivot index in both of its
 **   members is returned, so that the same quicksort function can be
 **   used with both partition and tripartition.
 *********************************************************************/
// This function was constructed from the pseudocode found on the
// "Quicksort" Wikipedia page.
struct pair partition(int *arr, int left, int right) {
    // These two lines offer two different pivot selection methods.
    // Either way the pivot value is stored in arr[right]. Choose one:
    int pivot = median(arr, left, right);
    // int pivot = arr[right];
    
    int j;
    // result.i keeps track of the first index that contains an element
    // greater than the pivot (unless result.i == j, in which case the 
    // value of result.i is yet to be discovered).
    struct pair result = {left, 0};

    // The loop invariant is that all elements from index left to
    // result.i - 1 (if any) contain values less than or equal to the
    // pivot value, and all elements from result.i to j - 1 (if any)
    // contain values greater than the pivot value.
    for (j = left; j < right; ++j) {
        // If less than the pivot, swap it into the element at index
        // result.i and increment result.i.
        if (arr[j] <= pivot) {
            if (result.i != j)
                swap(&arr[result.i], &arr[j]);
            ++result.i;
        }
    }
    // Finally, swap the pivot value from arr[right] into arr[result.i].
    swap(&arr[result.i], &arr[right]);

    // Assign result.i to result.n to mimic the behavior of tripartition
    // for compatibility purposes.
    result.n = result.i;
    return result;
}

/*********************************************************************
 ** Function: quicksort
 ** Description: If there is more than one element in the range,
 **   partitions the range into two (or three) subarrays of elements
 **   less than, (equal to,) and greater than a chosen "pivot" value,
 **   recursively calling itself for both (but not the "equal to"
 **   subarray, because it is already sorted).
 ** Parameters: int *arr - a pointer to the beginning of the array
 **               being sorted.
 **             int left - the first index of the range.
 **             int right - the last index of the range.
 ** Pre-Conditions: arr is not a null pointer, left and right are
 **   nonnegative integers such that left <= right, and right is a
 **   valid index of arr (right + 1 <= the size of the array).
 ** Post-Conditions: The elements from left to right are sorted in
 **   ascending order.
 ** Return: N/A
 *********************************************************************/
// This function was constructed from the pseudocode found on the
// "Quicksort" Wikipedia page.
void quicksort(int *arr, int left, int right) {
    if (left < right) {
        // These functions partition the elements based on their
        // relative value compared to a "pivot" value. Choose one:
        struct pair p = tripartition(arr, left, right);
        // struct pair p = partition(arr, left, right);
        
        // This function call performs quicksort on the values
        // smaller than the pivot value.
        quicksort(arr, left, p.i - 1);
        // This function call performs quicksort on the values
        // larger than the pivot value.
        quicksort(arr, p.n + 1, right);
    }
}

/*********************************************************************
 ** Function: merge
 ** Description: Merges two sorted subarrays so that the merged
 **   array is also sorted.
 ** Parameters: int *nums - points to the integer array to sort.
 **             int left - the first index of the lower subarray.
 **             int mid - the final index of the lower subarray.
 **             int right - the final index of the upper subarray.
 ** Pre-Conditions: nums is not a null pointer. left <= mid < right,
 **   where all three are nonnegative integers, and right is a valid
 **   index of nums (right + 1 <= size of the array). The subarrays
 **   from left to mid and mid + 1 to right are both already sorted
 **   in ascending order.
 ** Post-Conditions: The elements from left to right are sorted in
 **   ascending order.
 ** Return: N/A
 *********************************************************************/
void merge(int *nums, int left, int mid, int right){
    int i, j, lower_half, upper_half;
    int temp[(right-left)+1];

    // Assign lower_half and upper_half the indices of the first
    // (smallest) elements of the two sorted subarrays.
    lower_half=left;
    upper_half=mid+1;

    // Continue looping while neither subarray has been exhausted.
    for(i=0; (lower_half<=mid)&&(upper_half<=right); i++){
        // If the smallest element remaining in the lower subarray is
        // less than or equal to the smallest element remaining in
        // the upper subarray, assign it to the next position of the
        // temp array. Increment the beginning index of the unused
        // elements in the lower subarray.
        if(nums[lower_half]<=nums[upper_half]){
            temp[i]=nums[lower_half];
            lower_half++;
        }
        // Otherwise, assign the smallest element remaining in the
        // upper subarray to the next position of the temp array.
        // Increment the beginning index of the unused elements in
        // the upper subarray.
        else{
            temp[i]=nums[upper_half];
            upper_half++;
        }
    }

    // If the upper subarray was exhausted first, copy the remaining
    // elements of the lower subarray into the remaining elements of
    // the temp array.
    if(lower_half>mid)
        for(j=upper_half;j<=right;j++, i++)
            temp[i]=nums[j];
    // Otherwise, the lower subarray was exhausted first. Copy the
    // remaining elements of the upper subarray into the remaining
    // elements of the temp array.
    else
        for(j=lower_half;j<=mid;j++, i++)
            temp[i]=nums[j];

    // Copy the sorted temp array back into the nums array.
    for(j=0,i=left;i<=right;i++,j++)
        nums[i]=temp[j];
}

/*********************************************************************
 ** Function: merge_sort
 ** Description: If there is more than one element in the range
 **   [left, right], divides the indices into two subarrays,
 **   recursively calls itself for both, and merges the two sorted
 **   subarrays.
 ** Parameters: int *nums - points to the integer array to sort.
 **             int left - the lowest index of the array to sort.
 **             int right - the highest index of the array to sort.
 ** Pre-Conditions: nums is not a null pointer, left and right are
 **   nonnegative integers such that left <= right, and right is a
 **   valid index of nums (right + 1 <= the size of the array).
 ** Post-Conditions: The subarray with indices from left to right,
 **   inclusive, is sorted in ascending order.
 ** Return: N/A
 *********************************************************************/
void merge_sort(int *nums, int left, int right) {
    int mid;
    if(left<right) {
        mid=(right+left)/2;
        // This function call performs merge_sort on the left half of
        // the array.
        merge_sort(nums, left, mid);
        // This function call performs merge_sort on the right half of
        // the array.
        merge_sort(nums, mid+1, right);
        // This function call merges the two sorted subarrays.
        merge(nums, left, mid, right);
    }
}

/*********************************************************************
 ** Function: selection_sort
 ** Description: Selects the smallest element of the array and swaps
 **   it with the element in the 0-th position, then selects the
 **   second smallest element and swaps it into the first position.
 **   This process continues for all positions. Before loop i, the first
 **   i elements are in their final sorted positions.
 ** Parameters: int *nums - points to the integer array to sort.
 **             int size - the number of elements in the array.
 ** Pre-Conditions: nums is not a null pointer, and size is the non-
 **   negative number of elements in *nums.
 ** Post-Conditions: The array pointed to by nums is sorted in ascending
 **   order.
 ** Return: N/A
 *********************************************************************/
void selection_sort(int *nums, int size) {
    int i, j;
    int temp, min;

    // Finds the smallest element and places it in the 0-th position,
    // then the second smallest and the first position, etc.
    // Loop invariant: before loop i, the first i elements are in their
    // final sorted positions.
    for(i=0; i<size-1; i++) {
        min=i;
        // This loops finds the (i + 1)-th smallest element in the array.
        for(j=i; j<size; j++)
            if(nums[j]<nums[min])
                min=j;
        // The element occupying the i-th position is swapped with the
        // element identified as the (i+1)-th smallest of the array.
        temp=nums[i];
        nums[i]=nums[min];
        nums[min]=temp;
    }
}

/*********************************************************************
 ** Function: insertion_sort
 ** Description: In each loop iteration, the i-th element is inserted
 **   into the sorted subarray of the preceding elements. Each preceding
 **   element is shifted up one position: the (i-1)-th element moves into
 **   the i-th position (assuming it is larger than the i-th element),
 **   the (i-2)-th element into the (i-1)-th position, and so on, until
 **   an element smaller than the i-th element is found. Then, rather
 **   than shifting up this element, the i-th element is inserted into
 **   the array in the open position, preserving the sorted order of
 **   the subarray and increasing its size by one. Before loop i, the
 **   first i elements are in sorted order (although not necessarily
 **   in their final sorted positions).
 ** Parameters: int *nums - points to the integer array to sort.
 **             int size - the number of elements in the array.
 ** Pre-Conditions: nums is not a null pointer, and size is the non-
 **   negative number of elements in *nums.
 ** Post-Conditions: The array pointed to by nums is sorted in ascending
 **   order.
 ** Return: N/A
 *********************************************************************/
void insertion_sort(int *nums, int size) {
    int i, j;
    int temp;

    // Inserts the i-th element into the preceding sorted subarray.
    // Loop invariant: before loop i, the first i elements of the
    // array are in sorted order (but not their final positions).
    for(i=0; i<size; i++) {
        temp=nums[i];
        // This loop shifts each element up one position if it is
        // larger than temp (moving the "hole" for temp to be inserted
        // one position towards the front of the array).
        for(j=i; j>0 && nums[j-1]>temp; j--)
            nums[j]=nums[j-1];
        // Finally, temp is placed into the sorted subarray where it
        // belongs, preserving the loop invariant.
        nums[j]=temp;
    }
}

/*********************************************************************
 ** Function: bubble_sort
 ** Description: "Bubbles up" the largest element of the unsorted
 **   subarray in each loop iteration. Each element is compared to the
 **   next, starting at the beginning of the array, and swapped if in
 **   inverted order. This ensures that in each comparison, the next
 **   array element is compared with the largest of all the preceding
 **   elements. This process continues to the end of the unsorted
 **   subarray. Before loop i, the last i array elements are in their
 **   final sorted positions.
 ** Parameters: int *nums - points to the integer array to sort.
 **             int size - the number of elements in the array.
 ** Pre-Conditions: nums is not a null pointer, and size is the non-
 **   negative number of elements in *nums.
 ** Post-Conditions: The array pointed to by nums is sorted in ascending
 **   order.
 ** Return: N/A
 *********************************************************************/
void bubble_sort(int *nums, int size) {
    int i, j;
    int temp;

    // Moves the largest element to the last index, then the next
    // largest to the second to last index, etc.
    // Loop invariant: before loop i, the last i elements in the
    // array are in their final sorted positions.
    for(i=0; i<size; i++) {
        // "Bubbles up" the largest element in the unsorted subarray
        // into position size - i - 1.
        for(j=0; j<size-i-1; j++) {
            // If there is an inversion, swap the values of the two
            // adjacent elements.
            if(nums[j]>nums[j+1]) {
                temp=nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=temp;
            }
        }
    }
}

/*************************************************
 * Description: This adds an element to the array
 * and sets the contents to num
 * Params: address of array pointer to ints and
 *         address of size of the array
 * Returns: none
 * Post-conditions: size is increased by one and
 * nums points to new array with one more element
 * where the contents are the same with num at the end
 * Pre-conditions: nums points to valid array or NULL
 * and size is accurate number of elements in array >=0
 * **********************************************/
void add_num(int **nums, int *size, int num){
    int *old_nums, i;

    *size+=1;
    old_nums=*nums;
    *nums=(int *) malloc(sizeof(int)*(*size));

    for(i=0; i<*size-1; i++)
        (*nums)[i]=old_nums[i];
    (*nums)[*size-1]=num;

    free(old_nums);
}

/*************************************************
 * Description: This fills an array with contents
 * from a file
 * Params: address of array pointer to ints and
 *         address of size of the array
 * Returns: none
 * Post-conditions: array pointer is pointing to
 * valid array of integers or NULL and size has
 * a positive integer
 * Pre-conditions: nums points to valid array or NULL
 * and size is accurate number of elements in array >=0
 * **********************************************/
/*void fill_array(int **nums, int *size) {
  FILE *fptr;
  char filename[20], num[10];

  printf("Enter the filename: ");
  scanf("%s",filename);

  fptr=fopen(filename,"r");

  while(fscanf(fptr,"%s", num)!=EOF){
  add_num(nums, size, atoi(num));
  }

  fclose(fptr);
  }*/

void fill_array(int **nums, int *size) {
    FILE *fptr;
    char filename[20], num[10];
    int i = 0;

    printf("Enter the filename: ");
    scanf("%s",filename);
    fptr=fopen(filename,"r");
    printf("How many elements are there? ");
    scanf("%d", size);

    *nums = malloc(sizeof(int) * (*size));

    while( i < *size && fscanf(fptr,"%s", num) != EOF)
        (*nums)[i++] = atoi(num);

    fclose(fptr);
}

/*************************************************
 * Description: This prints the contents of an array
 * Params: array of integers and size of the array
 * Returns: none
 * Post-conditions: none
 * Pre-conditions: size is accurate number of
 *                 elements in the array >=0
 * **********************************************/
/*void print_array(int *nums, int size){
    int i;

    printf("The array elements are:\n");
    for(i=0; i<size; i++)
        printf("%d\t", nums[i]);
    printf("\n\n");
}*/
void print_array(int *nums, int left, int right){
    int i;

    printf("The array elements are:\n");
    for(i = left; i <= right; i++)
        printf("%d\t", nums[i]);
    printf("\n\n");
}
