# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
 config.vm.box = "https://download.gluster.org/pub/gluster/purpleidea/vagrant/fedora-22/fedora-22.box"
 config.hostmanager.enabled = true
 config.hostmanager.manage_host = true

 # By default, Vagrant wants to mount the code in /vagrant with NFSv3, which will fail. Let's
 # explicitly mount the code using NFSv4.
 config.vm.synced_folder ".", "/vagrant", type: "nfs", nfs_version: 4, nfs_udp: false

 # Create the "dev" box
 config.vm.define "dev" do |dev|
    dev.vm.host_name = "dros.example.com"
    dev.vm.synced_folder "..", "/home/vagrant/devel", type: "nfs", nfs_version: 4, nfs_udp: false

    dev.vm.provider :libvirt do |domain|
        domain.cpus = 4
        domain.graphics_type = "spice"
        domain.nested = true
        domain.memory = 2048
        domain.video_type = "qxl"
    end

    dev.vm.provision "shell", inline: <<-SHELL
      pushd /vagrant/
      bash ./setup.sh
    SHELL
 end
end
