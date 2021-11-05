!: @file test_permutations.f95
!! test program for the permutations module
!! displays all 24 permutations of (1, 2, 3, 4)

program test_permutations
  use permutations
  implicit none
  integer :: array(1:4)
  logical :: exists
  integer :: number
  
  number = 0
  exists = get_first_permutation(array, size(array))
  do while (exists)
     number = number + 1
     call print_permutation
     exists = get_next_permutation(array, size(array))
  end do

contains

  subroutine print_permutation
    integer :: i
    write(*, "(I3,': ',*(I3))") number, (array(i), i = 1, size(array))

    end subroutine print_permutation

end program test_permutations
