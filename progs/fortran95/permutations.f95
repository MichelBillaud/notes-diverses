module permutations

    implicit none
    private
    public :: get_first_permutation, get_next_permutation

contains

    function get_first_permutation(array, size) result(found)
        integer,  intent(IN)  :: size
        integer,  intent(OUT) :: array(1:size)
        logical :: found
        integer :: i

        found = (size >= 1)
        if (.not. found) return
      
        do i = 1, size
            array(i) = i
        end do
    end function get_first_permutation
    
    function get_next_permutation(array, size) result(found)
        integer, intent(IN)     ::  size
        integer, intent(INOUT)  :: array(1:size)
        logical                 :: found
        integer                 :: prefix_length, index
        
        prefix_length = find_prefix_length(array, size)
        found = (prefix_length > 0)
        if (.not. found) return           ! array contains the last permutation
        
        index = find_next_in_prefix(array, size, array(prefix_length))
        call swap(array(prefix_length), array(index))
        call reverse_suffix(array, size, prefix_length + 1)
    end function get_next_permutation

    !
    ! private part
    !
    function find_prefix_length(array, size) result(length)
        integer, intent(IN) ::  size
        integer, intent(IN) :: array(1:size) 
        integer             :: length
     
        length = size - 1
        do while ((length > 0) .and. (array(length) >= array(length + 1)))
            length = length - 1
        end do
    end function find_prefix_length

    function find_next_in_prefix(array, size, value) result(index)
        integer,  intent(IN)      ::  size, value
        integer,  intent(IN)      :: array(1:size)
        integer                   :: index

        index = size
        do while (array(index) <= value)
            index = index - 1
        end do
    end function find_next_in_prefix

    subroutine reverse_suffix(array, size, suffix_start)
        integer, intent(IN)      :: size, suffix_start
        integer, intent(INOUT)   :: array(1:size)

        integer :: left, right
        left = suffix_start
        right = size
        do while (left < right)
            call swap (array(left), array(right))
            left = left + 1
            right = right - 1
        end do   
    end subroutine reverse_suffix

    subroutine swap(a, b)
        integer, intent(inout) :: a, b
        integer :: c
        c = a
        a = b
        b = c
    end subroutine swap

end module permutations
