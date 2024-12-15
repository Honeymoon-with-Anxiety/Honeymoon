-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Počítač: 127.0.0.1
-- Vytvořeno: Čtv 07. lis 2024, 18:40
-- Verze serveru: 10.4.32-MariaDB
-- Verze PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Databáze: `zmeny_v_rozvrhu`
--

-- --------------------------------------------------------

--
-- Struktura tabulky `zmeny`
--

CREATE TABLE `zmeny` (
  `id` int(11) NOT NULL,
  `trida` varchar(4) NOT NULL,
  `hodina` int(4) NOT NULL,
  `predmet` varchar(4) NOT NULL,
  `skupina` varchar(4) NOT NULL,
  `ucebna` varchar(4) NOT NULL,
  `zmena` varchar(10) NOT NULL,
  `ucitel` varchar(4) NOT NULL,
  `poznamky` text NOT NULL,
  `datum` date NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_czech_ci;

--
-- Vypisuji data pro tabulku `zmeny`
--

INSERT INTO `zmeny` (`id`, `trida`, `hodina`, `predmet`, `skupina`, `ucebna`, `zmena`, `ucitel`, `poznamky`, `datum`) VALUES
(1, 'S3', 1, 'STT', 'Pra1', 'SL1', 'supluje', 'Do', '(Ze)', '2024-11-06'),
(2, 'S3', 2, 'CNC', 'Pra1', 'NC', 'supluje', 'Fb', '(Ze)', '2024-11-06'),
(3, 'S3', 3, 'STT', 'Pra1', 'SL1', 'supluje', 'Do', '(Ze)', '2024-11-06'),
(4, 'E4A', 1, 'TVP', 'E4A', 'VY1', 'supluje', 'Ma', '(Ze)', '2024-11-07'),
(5, 'S3', 5, 'TEV', 'S3', 'TEL2', 'vyjmuto', 'Mš', 'Zrušeno pro nemoc', '2024-11-07');

--
-- Indexy pro exportované tabulky
--

--
-- Indexy pro tabulku `zmeny`
--
ALTER TABLE `zmeny`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pro tabulky
--

--
-- AUTO_INCREMENT pro tabulku `zmeny`
--
ALTER TABLE `zmeny`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
