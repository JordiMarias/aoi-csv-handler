# Dockerfile to be able to configure Clion for the environment
# docker build -t csv-handler-clion -f clion.Dockerfile .
# docker run -d --cap-add sys_ptrace -p 2223:22 --name clion_remote_env_csv csv-handler-clion

FROM alpine:3.12.1

RUN apk update &&\
    apk upgrade &&\
    apk add bash bash-doc bash-completion gcc=9.3.0-r2 cmake=3.17.2-r0 make=4.3-r0 boost=1.72.0-r6 boost-dev=1.72.0-r6 openssh cppunit-dev=1.15.1-r0

RUN apk add --update g++ clang gdb cmake make ninja autoconf automake dos2unix tar rsync python3 \
  && rm  -rf /tmp/* /var/cache/apk/*

RUN echo "root:root" | chpasswd

RUN ( \
	echo 'Port 22'; \
	echo '#AddressFamily any'; \
	echo '#ListenAddress 0.0.0.0'; \
	echo '#ListenAddress ::'; \
	echo 'HostKey /etc/ssh/ssh_host_rsa_key'; \
	echo 'HostKey /etc/ssh/ssh_host_dsa_key'; \
	echo 'HostKey /etc/ssh/ssh_host_ecdsa_key'; \
	echo 'HostKey /etc/ssh/ssh_host_ed25519_key'; \
	echo 'PermitRootLogin yes'; \
	echo 'PasswordAuthentication yes'; \
	echo 'AuthorizedKeysFile .ssh/authorized_keys'; \
	echo 'Subsystem sftp /usr/lib/ssh/sftp-server'; \
  ) > /etc/sshd_config_test_clion

RUN /usr/bin/ssh-keygen -A
RUN ssh-keygen -t rsa -b 4096 -f  /etc/ssh/ssh_host_key

EXPOSE 22
CMD ["/usr/sbin/sshd", "-D", "-f", "/etc/sshd_config_test_clion"]