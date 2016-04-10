# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
 config.vm.box = "fedora/23-cloud-base"

 # By default, Vagrant wants to mount the code in /vagrant with NFSv3, which will fail. Let's
 # explicitly mount the code using NFSv4.
 config.vm.synced_folder ".", "/vagrant", type: "nfs", nfs_version: 4, nfs_udp: false

 if Vagrant.has_plugin?("vagrant-cachier")
    config.cache.scope = :box
    config.cache.synced_folder_opts = {
        type: :nfs,
        mount_options: ['rw', 'vers=4', 'tcp']
    }
 end

 # Create the "dev" box
 config.vm.define "dev" do |dev|
    dev.vm.host_name = "dros.example.com"
    dev.vm.synced_folder "..", "/home/vagrant/devel", type: "nfs", nfs_version: 4, nfs_udp: false

    dev.vm.provider :libvirt do |domain|
        domain.cpus = 2
        domain.graphics_type = "spice"
        domain.nested = true
        domain.memory = 4096
        domain.video_type = "qxl"

        # The virtual host will ignore fsync calls to improve performance.
        # In the event of corruption, vagrant destroy and vagrant up.
        domain.volume_cache = "unsafe"
    end

    dev.vm.provision "shell", inline: <<-SHELL
        set -e
        
        echo "Installing Ansible in order to configure the system..."
        sudo dnf -y install python2 python2-dnf libselinux-python ansible
        
        if [ ! -f /tmp/ansible_inventory ]; then
            echo -e "localhost ansible_connection=local" >> /tmp/ansible_inventory
        fi
        
        ansible-playbook --inventory-file=/tmp/ansible_inventory \
            /home/vagrant/devel/dros/ansible/dev-playbook.yml
     SHELL
 end
end
