program branch_misprediction
  use iso_fortran_env, only : REAL64, INT64

  implicit none

  integer, parameter :: dp = REAL64, long = INT64

  integer, parameter :: repetitions = 20
  integer, parameter :: N = 20*1024*1024

  real :: data(N)
  real :: sum

  call random_number(data)
  data = data * 10

  ! TODO sort the data 

  sum = test_memory(data, 6.0)
  write(*,*) 'Sum', sum

  
  contains 
    function test_memory(data, value) result(sum)

      real, intent(in) :: data(:)
      real :: value
      real :: sum

      integer :: t, i

      integer(kind=long) :: t0, t1, tick
      real(kind=dp) :: r, secs

      sum = 0

      call system_clock(count=t0)
      do t = 1, repetitions
        do i = 1, N
           if (data(i) < value) then
              sum = sum + data(i)
           end if
        end do
      end do

      call system_clock(count=t1, count_rate=tick)
      secs = (dble (t1-t0) / dble(tick))

      write(*,*) 'Time: ', secs

    end function test_memory
end program
