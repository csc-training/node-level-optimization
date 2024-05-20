program matrix_multiply
  use iso_fortran_env, only : REAL64, INT64

  implicit none
  integer, parameter :: dp = REAL64, long = INT64
  real(dp), allocatable, dimension(:,:) :: a, b, c
  character(len=20) :: arg(3)
  integer :: maxiter, N
  integer :: i, iter

  integer(kind=long) :: t0, t1, tick
  real(kind=dp) :: r, secs

  if (command_argument_count() /= 2) then
     write(*,*) 'usage: ./matmul number-of-iterations array-size'
     stop
  else
     do i = 1, 2
        call get_command_argument(i, arg(i))
     end do
     read(arg(1),*) maxiter
     read(arg(2),*) N
  end if

  allocate(a(N, N), b(N, N), c(N, N))

  ! init to some values
  a = 0.5_dp
  b = 0.2_dp

  secs = 0.0_dp
  do iter = 1, maxiter
     call system_clock(count=t0)
     call matmul(a, b, c, N)
     call system_clock(count=t1, count_rate=tick)
     secs = secs + (dble (t1-t0) / dble(tick))
  end do

  write(*,'(A, I0, G10.4,A,G12.6)') &
       'Matrix multiplication , N=', N, 1.0d3*secs/dble(maxiter), ' msec. Check=', &
       c(N,N)


contains

  ! square-matrix matmul
  subroutine matmul(a, b, c, N)
    implicit none
    integer, intent(in) :: N
    real(kind=dp), intent(in) :: a(:,:), b(:,:)
    real(kind=dp), intent(out) :: c(:,:)

    integer :: i, j, k
    integer(kind=long) :: t0, t1, tick

    c = 0.0_dp
    do j = 1, N
       do i = 1, N
          do k = 1, N
             c(i,j) = c(i,j) + a(i,k) * b(k,j)
          end do
       end do
    end do

  end subroutine matmul

end program matrix_multiply

