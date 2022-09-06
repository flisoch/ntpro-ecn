sudo -u postgres bash -c "psql -c \"DROP ROLE IF EXISTS daler_exchange;\""
sudo -u postgres bash -c "psql -c \"DROP DATABASE IF EXISTS daler_exchange;\""
sudo -u postgres bash -c "psql -c \"CREATE USER daler_exchange WITH PASSWORD 'dalerexchange';\""
sudo -u postgres bash -c "psql -c \"CREATE DATABASE daler_exchange;\""
