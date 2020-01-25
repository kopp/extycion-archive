% Skifahren
% Michael Kopp

% solves the dgl
%   s'' + k s' = g A     with s(0) = 0 , s'(0) = 0
% using three different methods and comparing them to the analytical solution
% (the prime denotes deviation with respect to time)
%
% the dgl is rewritten in two first order dgls
%   v  = s'
%   v' = g A - k v
% and in the following, the vector x will be x = [s' ; s] 


%
% parameters:
gamma = 17./180*pi
muG = 0.1 
global k = 0.004 
k
global g = 9.81 
g
global A = sin(gamma) - muG * cos(gamma) ;
dt = 5 
t_end = 60 
dt
% initial conditions:
x0 = [0 ; 0 ] 
% timesteps for which the solution shall be computed:
t = [0 : dt : t_end ] ;


%
% the dgl for matlab: x' = f(x,t) 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% change the dgl here  %%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function xdot = f( x , t )
	% to make use of global variables:
	global g A k
	xdot = zeros(2,1) ;
	xdot(2) = x(1) ;
	xdot(1) = g .* A - k .* x(1) .^ 2 ;
end

% from now on there will be only computation relying on this function f(x) 


%
% 1. lsode -- octave's built in tool. See `help lsode`
x_lsode = lsode("f",x0,t) ;

%
% 2.a euler
x_euler(:,1) = x0 ;
for i = [2:length(t)]
	% this elements will be computed now -- for now enter zeros:
	x_euler(:,i) = zeros(2,1) ;
	% acceleration:
	a = g .* A  - k .* x_euler(1,i-1) .^ 2 ;
	% v_new = v + a * dt
	x_euler(1,i) = x_euler(1,i-1) + a .* dt ;
	% s_new = s + v * dt
	x_euler(2,i) = x_euler(2,i-1) + x_euler(1,i-1) *dt ;
end

%
% 2.b euler (not v(t) is used to update s(t) but (v(t)+v(t-dt))/2)
x_euler_diff(:,1) = x0 ;
for i = [2:length(t)]
	% this elements will be computed now -- for now enter zeros:
	x_euler_diff(:,i) = zeros(2,1) ;
	% acceleration:
	a = g .* A  - k .* x_euler_diff(1,i-1) .^ 2 ;
	% v_new = v + a * dt
	x_euler_diff(1,i) = x_euler_diff(1,i-1) + a .* dt ;
	% s_new = s + v * dt
	x_euler_diff(2,i) = x_euler_diff(2,i-1) + (x_euler_diff(1,i) + x_euler_diff(1,i-1)) *dt / 2 ;
end


% 
% 3. runge kutta (of order 4 -- vgl Bronstein(7) 19.4.1.2)
x_rk4(:,1) =x0 ;
for i = [2:length(t)]
	x_rk4(:,i) = zeros(2,1) ;
	k1 = dt .* f( x_rk4(:,i-1)           , (i-1)*dt ) ;
	k2 = dt .* f( x_rk4(:,i-1) + k1 ./ 2 , (i-1)*dt ) ;
	k3 = dt .* f( x_rk4(:,i-1) + k2 ./ 2 , (i-1)*dt ) ;
	k4 = dt .* f( x_rk4(:,i-1) + k3      , (i-1)*dt ) ;
	x_rk4(:,i) = x_rk4(:,i-1) + (k1+2.*k2+2.*k3+k4) ./ 6 ;
end


%
% 4. analytical
function x = xana(t)
	global g A k
	x = log( cosh( sqrt( g * k * A ) .* t ) ) ./ k ;
end
function v = vana(t)
	global g A k
	v = sqrt( g * A / k ) * tanh( sqrt(g * A * k ) .* t ) ;
end


% 
% output
% velocities
" the calculation is done -- enjoy the results: "
" positions: "
plot( ...
t' ,  x_lsode(:,1) , "+;lsode;" , ...
t' , x_euler(1,:)' , "*;euler;" , ...
t' , x_euler_diff(1,:)' , "o;euler diff;" , ...
t' , x_rk4(1,:)' , "x;rk4;" , ...
t' , vana(t') , ";analytical;" ...
) ;
legend( "boxon" , "location" , "northwest" ) ;
xlabel "time"
ylabel "velocitie v"
print( "velocities.eps" , "-color" ) ;

" press any key to go on "
kbhit
" velocities "
% positions
plot( ...
t' ,  x_lsode(:,2) , "+;lsode;" , ...
t' , x_euler(2,:)' , "*;euler;" , ...
t' , x_euler_diff(2,:)' , "o;euler diff;" , ...
t' , x_rk4(2,:)' , "x;rk4;" , ...
t' , xana(t') , ";analytical;" ...
) ;
legend( "boxon" , "location" , "northwest" ) ;
xlabel "time"
ylabel "position s"
print( "positions.eps" , "-color" ) ;




