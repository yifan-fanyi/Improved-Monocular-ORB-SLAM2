% read from poses
filename = 'x10.txt';qr(lastposition);

groundtruth = [];
hold on;
while fgetl(fid) ~= -1, % end of line check

    fseek(fid, lastposition, 'bof');
    line = textscan(fid,'%f %f %f %f %f %f %f %f %f %f %f %f\n',1);
    line = [line{:}];
    transform = vec2mat(line,4);

    groundtruth = [groundtruth; [transform(1,4), transform(3,4)]];
    lastposition = ftell(fid);
    disp(['lastposition:',num2str(lastposition)]);

end

% display ground truth
scatter(groundtruth(:,1),groundtruth(:,2));

fclose(fid);