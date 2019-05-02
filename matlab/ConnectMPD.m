%clear all         % Clean the Workspace and Commands Window
delete(instrfind({'Port'},{'COM4'}));        % Delete some posible previous configuration for the port used for the Xbee (COM4).

TestDuration=30;         % Duration of the test in seconds
Rechazados=0;
extraDelay=35;
delay=10;         % Delay in the Arduino code
SampleLength=round(TestDuration*1000/(delay+extraDelay));       % Samples=Duration[s]*(1000ms/1s)*(1sample/delay[ms])

tic         % Initiacilates tic funtion (used to track the time which every sample is taken at).
rate = 9600;         % 9600 bits per seconds which compared with the 50 seconds delay in the Arduino code is negligible
s = serial('COM4', 'BaudRate',rate,'TimeOut',10,'Terminator','LF');        % Object created to represent the COM port, some inputs are set here
s.InputBufferSize = 1000000;    
   
fopen(s);         % Open port communication

data=zeros(8,SampleLength);         % 7x100 matrix initialised with zeros which will be used to save every axis from the sensor (3 acceleration axis and 3 gyroscope axis) and the time vector.
i=1;
lapse=toc;
stepCount=0;
while i<=SampleLength         % When the SampleLength limit is reached the processor exits the loop and continues executing the rest of the code.
    sample=fscanf(s,'%i');
    if length(sample)==6;        % every reading block is checked to be completed with the 6 variables expected, as sometimes it is damaged and must be eliminated leaving those zeros behind.
        data(:,i)=vertcat(sample,toc,0);       % Variables are added to the matrix with the corresponding time extracted from “toc” function.
       
        if (data(2,i)>18000)&(toc-lapse>0.35);
        stepCount=stepCount+1
        lapse=toc;
        data(8,i)=5000;
        end
        
        i=i+1;
    else
        Rechazados=Rechazados+1;
    end
    
end
fclose(s);        % Close serial port bus

% Matrix divided into 7 arrays that are plotted to be visually analysed
Ax=data(1,:);
Ay=data(2,:);
Az=data(3,:);
Gx=data(4,:);
Gy=data(5,:);
Gz=data(6,:);
Time=data(7,:);
Samples=data(8,:);

plot(Time,Ax,Time,Ay,Time,Az,Time,Gx,Time,Gy,Time,Gz);
legend('Ax','Ay','Az','Gx','Gy','Gz');
% plot(Time,Ay,Time,Samples);
